#include "Adafruit_WS2801.h"

Adafruit_WS2801 strip = Adafruit_WS2801(128);



void setup() 
{
  strip.begin();
  strip.show();
}

void loop() 
{
  set_red();
  delay(200);
  set_off();
  delay(200);
}

void set_off(void)
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void set_red(void)
{
  for(int i=0; i<128; ++i)
  {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

