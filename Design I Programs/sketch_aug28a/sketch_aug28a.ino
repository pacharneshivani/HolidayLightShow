#include <ESP8266WiFi.h>
 
const char* ssid     = "HolidayLightsController";
const char* password = "LightsPassword";
uint32_t current_millis = 0, previous_millis = 0, previous_millis2 = 0, previous_millis3 = 0, 
          delay_time = 300, delay_time2 = 4000, delay_time3 = 500;
uint8_t led_state = 0;
 
void setup() 
{
  Serial.begin(57600);
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  delay(300);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
 
int value = 0;
 
void loop() 
{
  current_millis = millis();
  if((current_millis - previous_millis) >= delay_time)
  {
    previous_millis = current_millis;
    if(led_state == 0)
    {
      digitalWrite(0, HIGH);
      led_state = 1;
    }
    else if(led_state == 1)
    {
      digitalWrite(0, LOW);
      led_state = 0; 
    }
    
  }
  if((current_millis - previous_millis2) >= delay_time2)
  {
    previous_millis2 = current_millis;
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Netmask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.println("");
  }
}
