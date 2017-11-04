#include<ESP8266WiFi.h>

const char ssid[] = "HolidayLightsController";
const char pass[] = "LightsPassword";
uint8_t character = 4;

const uint32_t port = 1234;
const char *host = "192.168.0.1";
int status = WL_IDLE_STATUS;
uint32_t send_count = 0;
//const char host[] = "192.168.0.1";

WiFiClient client;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  Serial.begin(115200);
  delay(500);
  delay(200);
  Serial.println("Attempting to connect to Wi-Fi network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting");
  WiFi.begin(ssid, pass);
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
    Serial.println("Connection failed");
    Serial.println("Wait 5 seconds....");
    delay(5000);
    return;
  } 
}

void loop() 
{
  
  client.print("Send this data to server");
  client.print(send_count);
  send_count++;
  
  //String line = client.readStringUntil('\r');
  //client.println(line);
  //Serial.println("Closing connection");
  //client.stop();
  //Serial.println("Wait 2 seconds.....");
  delay(200);
  digitalWrite(0, LOW);
  delay(200);
  digitalWrite(0, HIGH);
}
