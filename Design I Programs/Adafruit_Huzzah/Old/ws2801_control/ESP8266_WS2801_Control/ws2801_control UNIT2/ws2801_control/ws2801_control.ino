#include "SPI.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

#define NUM_LEDS (128) //Number of LEDs to be controlled. 128 LEDs per strip.
#define SPI_FREQUENCY (2500000L) //SPI frequency defined as 2.5 MHz. Adjust as needed
#define HEARTBEAT_COUNT (30000) //Can be changed to alter the frequency of the heartbeat LED
#define HEARTBEAT_LED (0) //Output pin connected to the heartbeat LED

const char ssid[] = "HolidayLightsController"; //Name of the network we are connecting to 
const char pswd[] = "HolidayLightsController"; //Password for the network we are connecting to
const uint32_t local_port = 5005; //Port we will listen on for UDP data

IPAddress ip_address(192, 168, 0, 3);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet (255, 255, 255, 0);

uint8_t led_data[NUM_LEDS * 3]; //Allocate 3 bytes per LED
char packet_buffer[512]; //Allocate 512 bytes for a buffer of incoming UDP data

WiFiUDP udp_connection; //Create object of WiFiUDP class

void config_wifi(void) //Helper function to configure our WiFi connection
{ 
  WiFi.mode(WIFI_STA);
  WiFi.config(ip_address, gateway, subnet);
  WiFi.begin(ssid, pswd);
  while(WiFi.status() != WL_CONNECTED)
  {
    yield();
    do_heartbeat();
  }
  udp_connection.begin(local_port);
}

void print_wifi_status() //Can be used for debugging
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  int32_t rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void config_heartbeat(void) //Configure our heartbeat LED
{
  pinMode(HEARTBEAT_LED, OUTPUT);
  digitalWrite(HEARTBEAT_LED, LOW);
}

void do_heartbeat(void) //Called repeatedly. Toggles LED when HEARTBEAT_COUNT is reached
{
  static uint32_t cycle_count = 0;
  static uint8_t led_status = 0;
  cycle_count++;
  if(cycle_count >= HEARTBEAT_COUNT)
  {
    digitalWrite(HEARTBEAT_LED, led_status);
    led_status = !led_status;
    cycle_count = 0;
  }
}

void config_spi(void) //Configure out SPI module to communicate with the LEDs
{
  SPI.begin();
  SPI.setFrequency(SPI_FREQUENCY);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
}

//Each LED on the strip is represented by 3 bytes of data. All data is stored
//in an array and when this function is called all data in the array will be
//pushed to the strip via the SPI bus.
void update_lights(void)
{ 
  uint32_t num_bytes = NUM_LEDS * 3;
  for(int i=0; i<num_bytes; i++)
  {   
    SPI.transfer(led_data[i]);
  }
  yield();
}

void set_pixel_color(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  if(n < NUM_LEDS)
  {
    uint8_t *p = &led_data[n * 3];
    *p++ = r;
    *p++ = g;
    *p++ = b;
  }
}

void lights_red(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 255, 0, 0);
  }
  update_lights();
}

void lights_green(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 255, 0);
  }
  update_lights();
}

void lights_blue(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 0, 255);
  }
  update_lights();
}

void lights_off(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 0, 0);
  }
  update_lights();
}

void chase_to_end(void)
{
  for(int i=NUM_LEDS; i > 0; i--)
  {
    for(int j = 0; j < i; j++)
    {
      set_pixel_color(j, 255, 0, 0);
      if(j > 0)
      {
        set_pixel_color((j-1), 0, 0, 0);
      }
      update_lights();
    }
  }
}

void chase_to_end_two(void)
{
  uint32_t current_time = 0, previous_time = 0, delay_time = 5;
  for(int i=NUM_LEDS; i>0; i-=2)
  {
    for(int j=0; j<i; j+=2)
    {
      set_pixel_color(j, 178, 34, 34);
      set_pixel_color((j+1), 165, 42, 42);
      if(j>1)
      {
        set_pixel_color((j-1), 0, 0, 0);
        set_pixel_color((j-2), 0, 0, 0);
      }
      
      while((current_time - previous_time) <= delay_time)
      {
        do_heartbeat();
        current_time = millis();
      }
      previous_time = current_time;
      update_lights();
      yield();
    }
  }
}

void fade_in(String color)
{
  uint32_t current_time = 0, previous_time = 0, delay_time = 25;
  if(color == "RED")
  {
    for(int i=0; i<255; i++)
    {
      for(int j=0; j<NUM_LEDS; j++)
      {
        set_pixel_color(j, i, 0, 0);
      }
      while((current_time - previous_time) <= delay_time)
      {
        do_heartbeat();
        current_time = millis();
      }
      update_lights();
      yield();
    }
  }
}

void full_bright(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 255, 255, 255);
  }
  update_lights();
}

void lights_rgb(void)
{
  for(int i=0; i<43; i++)
  {
    set_pixel_color(i, 255, 0, 0);
  }
  for(int i=43; i<85; i++)
  {
    set_pixel_color(i, 0, 255, 0);
  }
  for(int i=85; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 0, 255);
  }
  update_lights();
}

void update_state(String server_command)
{
  if(server_command == "RED")
    {
      lights_red();
    }
    else if(server_command == "BLUE")
    {
      lights_blue();
    }
    else if(server_command == "GREEN")
    {
      lights_green();
    }
    else if(server_command == "OFF")
    {
      lights_off();
    }
    else if(server_command == "CHASE")
    {
      //chase_to_end_two();
      //fade_in("RED");
      lights_rgb();
    }
    else if(server_command == "BRIGHT")
    {
      full_bright();
    }
}

uint8_t get_network_data(void)
{
  uint32_t packet_size = 0, packet_length = 0;
  packet_size = udp_connection.parsePacket();
  if(packet_size)
  {
    packet_length = udp_connection.read(packet_buffer, 512);
    if(packet_length > 0)
    {
      packet_buffer[packet_length] = 0;
      return 1; 
    }
  }
  else
  {
    return 0;
  }
}

void setup() 
{
  config_heartbeat();
  config_spi();
  lights_off();
  config_wifi();
}

void loop() 
{ 
  if(get_network_data())
  {
    update_state(packet_buffer);
  }
  do_heartbeat();
}
