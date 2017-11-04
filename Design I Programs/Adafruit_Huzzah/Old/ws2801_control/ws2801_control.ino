#include "SPI.h"
//#include "ESP8266WiFi.h"

#define NUM_LEDS (128)
#define SPI_CLOCK_DIV (2)
#define HEARTBEAT_COUNT (25000)
#define HEARTBEAT_LED (13)

uint8_t led_data[NUM_LEDS * 3];

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
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV);
}

void update_lights(void)
{ 
  uint16_t num_bytes = NUM_LEDS * 3;
  for(int i=0; i<num_bytes; i++)
  {
    SPI.transfer(led_data[i]);
  }
  //delay(1);
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

void fade_in(void)
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    for(int j=0; j<NUM_LEDS; j++)
    {
      set_pixel_color(j, i, 0, 0);
    }
    delay(10);
    update_lights();
  }
}


void setup() 
{
  config_heartbeat();
  config_spi();
  //WiFi.disconnect();
  //WiFi.mode(WIFI_OFF);
  //WiFi.forceSleepBegin();
  Serial.begin(230400);
}

void loop() 
{
  static uint32_t current_millis = 0, previous_millis = 0, delay_time = 300;
  static uint8_t led_color = 0;
  current_millis = millis();
  if((current_millis - previous_millis) >= delay_time)
  {
    if(led_color == 0)
    {
      lights_red();
      led_color++;
    }
    else if(led_color == 1)
    {
      lights_green();
      led_color++;
    }
    else if(led_color == 2)
    {
      lights_blue();
      led_color++;
    }
    else if(led_color == 3)
    {
      lights_off();
      led_color++;
    }
    else if(led_color == 4)
    {
      fade_in();
      led_color++;
    }
    else if(led_color == 5)
    {
      lights_off();
      led_color = 0;
    }
    update_lights();
    previous_millis = current_millis; 
  }
  do_heartbeat();
}
