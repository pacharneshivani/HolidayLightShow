#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


int status = WL_IDLE_STATUS;
String server_command;
const char ssid[] = "HolidayLightsController"; //  your network SSID (name)
const char pass[] = "LightsPassword";    // your network password (use for WPA, or use as key for WEP)
//int keyIndex = 0;            // your network key Index number (needed only for WEP)
const unsigned int localPort = 5005;      // local port to listen on
unsigned int count = 0;
//unsigned int current_time, previous_time, loop_time;
char packetBuffer[255]; //buffer to hold incoming packet
//const char  ReplyBuffer[] = "acknowledged";       // a string to send back

WiFiUDP Udp;

void setup() 
{
  Serial.begin(115200);
  delay(200);
  Serial.println("");
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  
  Serial.println("Attempting to connect to Wi-Fi network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting");
  WiFi.begin(ssid, pass);
  //WiFi.config(ip, gateway, subnet);
  unsigned int count = 0;
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to access point");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);
}

void loop() 
{
  
  static String level1, level2, level3, level4, level5, level6, level7;
  static float f_level1, f_level2, f_level3, f_level4, f_level5, f_level6, f_level7;
  static float f_level1_scaled, f_level2_scaled, f_level3_scaled, f_level4_scaled, f_level5_scaled, f_level6_scaled, f_level7_scaled;
  static int packetSize;
  packetSize = Udp.parsePacket();
  if (packetSize) 
  {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) 
    {
      packetBuffer[len] = 0;  
    }
    
      level1 = String(packetBuffer[1]) + String(packetBuffer[2]) + String(packetBuffer[3]);
      level2 = String(packetBuffer[5]) + String(packetBuffer[6]) + String(packetBuffer[7]);
      level3 = String(packetBuffer[9]) + String(packetBuffer[10]) + String(packetBuffer[11]);
      level4 = String(packetBuffer[13]) + String(packetBuffer[14]) + String(packetBuffer[15]);
      level5 = String(packetBuffer[17]) + String(packetBuffer[18]) + String(packetBuffer[19]);
      level6 = String(packetBuffer[21]) + String(packetBuffer[22]) + String(packetBuffer[23]);
      level7 = String(packetBuffer[25]) + String(packetBuffer[26]) + String(packetBuffer[27]);
      
      f_level1 = level1.toFloat();
      f_level2 = level2.toFloat();
      f_level3 = level3.toFloat();
      f_level4 = level4.toFloat();
      f_level5 = level5.toFloat();
      f_level6 = level6.toFloat();
      f_level7 = level7.toFloat();
      
      f_level1_scaled = f_level1 * 1024;
      f_level2_scaled = f_level2 * 1024;
      f_level3_scaled = f_level3 * 1024;
      f_level4_scaled = f_level4 * 1024;
      f_level5_scaled = f_level5 * 1024;
      f_level6_scaled = f_level6 * 1024;
      f_level7_scaled = f_level7 * 1024;
      
      analogWrite(12, f_level1_scaled);
      analogWrite(13, f_level2_scaled);
      analogWrite(14, f_level3_scaled);
      analogWrite(15, f_level4_scaled);
      analogWrite(16, f_level5_scaled);
      analogWrite(2, f_level6_scaled);
      analogWrite(4, f_level7_scaled);
  }
}
   
void printWifiStatus() 
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
