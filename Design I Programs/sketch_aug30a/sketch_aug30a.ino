#include<ESP8266WiFi.h>

const char ssid[] = "HolidayLightsController";
const char pass[] = "LightsPassword";
const char host[] = "192.168.0.1";
const uint32_t port = 1234;
uint32_t previous_millis = 0, current_millis = 0, delay_millis = 500, led_state = 0;
const IPAddress ip(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);
int status = WL_IDLE_STATUS;
uint32_t send_count = 0;

WiFiClient client;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  Serial.begin(115200);
  delay(500);
  Serial.println("Attempting to connect to Wi-Fi network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting");
  WiFi.begin(ssid, pass);
  //WiFi.config(ip, gateway, subnet);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to access point");
  Serial.print("Connecting to: ");
  Serial.println(host);
  if(!client.connect(host, port))
  {
    Serial.println("Connection failed.");
    Serial.println("Waiting 2 seconds...");
    delay(2000);
    if(!client.connect(host, port))
    {
      Serial.println("Connection failed again...");
    }
  }
}

void loop() 
{
  if(!client.connected())
  {
    Serial.println("Conncection failed");
    Serial.print("Waiting 5 seconds");
    for(uint8_t i = 0; i < 20; ++i)
    {
      Serial.print(".");
      delay(250);
    }
    Serial.println("");
    client.connect(host, port);
    if(client.connected())
    {
      Serial.println("Reconnected");
    }
  }
  current_millis = millis();
  if((current_millis - previous_millis) >= delay_millis)
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
    client.print(send_count);
    
    if(client.connected())
    {
      send_count++;
      send_count++;
      Serial.println("");
      //Serial.println("Client is connected... maybe data isn't being received");
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
}
