#include "SPI.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

#define NUM_LEDS (128)
#define SPI_FREQUENCY (2000000L)
#define HEARTBEAT_COUNT (20000)
#define HEARTBEAT_LED (0)

const char ssid[] = "HolidayLightsController";
const char pswd[] = "HolidayLightsController";
const uint32_t local_port = 5005;

uint8_t led_data[NUM_LEDS * 3];
char packet_buffer[512];

WiFiUDP udp_connection;

void config_wifi(void)
{
  Serial.println("Attempting to connect to Wi-Fi network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting...");
  WiFi.begin(ssid, pswd);
  while(WiFi.status() != WL_CONNECTED)
  {
    yield();
    do_heartbeat();
  }
  Serial.println("");
  Serial.println("Connected to access point!");
  print_wifi_status();
  udp_connection.begin(local_port);
}

void print_wifi_status() 
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

void config_heartbeat(void)
{
  pinMode(HEARTBEAT_LED, OUTPUT);
  digitalWrite(HEARTBEAT_LED, LOW);
}

void do_heartbeat(void)
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

void config_spi(void)
{
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setFrequency(SPI_FREQUENCY);
  SPI.begin();
}

void update_lights(void)
{ 
  uint32_t num_bytes = NUM_LEDS * 3;
  for(int i=0; i<num_bytes; i++)
  {   
    SPI.transfer(led_data[i]);
  }
  delay(1);
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
}

void lights_green(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 255, 0);
  }
}

void lights_blue(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 0, 255);
  }
}

void lights_off(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    set_pixel_color(i, 0, 0, 0);
  }
}

void chase_to_end(void)
{
  for(int i=NUM_LEDS; i > 0; i-=2)
  {
    for(int j = 0; j < i; j+=2)
    {
      set_pixel_color(j, 255, 0, 0);
      set_pixel_color(j+1, 255, 0, 0);
      if(j > 0)
      {
        set_pixel_color((j-1), 0, 0, 0);
        set_pixel_color(j-2, 0, 0,0);
      }
      update_lights();
    }
 }
}


void setup() 
{
  Serial.begin(115200);
  config_heartbeat();
  config_spi();
  config_wifi();
}

void loop() 
{
  static uint32_t packet_size = 0, len = 0;
  static uint32_t current_time = 0, previous_time = 0, delay_time = 75, lights_status = 0;
  static int32_t rssi = 0;
  static String server_command = "";
  current_time = millis();
  packet_size = udp_connection.parsePacket();
  if(packet_size)
  {
    len = udp_connection.read(packet_buffer, 512);
    if(len > 0)
    {
      packet_buffer[len] = 0;
    }
    Serial.println(packet_buffer);
    rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
    server_command = packet_buffer;
    if(server_command == "RED")
    {
      lights_red();
      update_lights();
    }
    else if(server_command == "BLUE")
    {
      lights_blue();
      update_lights();
    }
    else if(server_command == "GREEN")
    {
      lights_green();
      update_lights();
    }
    else if(server_command == "OFF")
    {
      lights_off();
      update_lights();
    }
    else if(server_command == "CHASE")
    {
      chase_to_end();
    }
  }
  do_heartbeat();
}
