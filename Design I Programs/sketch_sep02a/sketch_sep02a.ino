#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
String server_command;
const char ssid[] = "HolidayLightsController"; //  your network SSID (name)
const char pass[] = "LightsPassword";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int led_state = 0;
const unsigned int localPort = 5005;      // local port to listen on
//unsigned int current_time, previous_time, loop_time;
char packetBuffer[16]; //buffer to hold incoming packet
//const char  ReplyBuffer[] = "acknowledged";       // a string to send back

WiFiUDP Udp;

void setup() 
{
  //Initialize serial and wait for port to open:
  //delay(1000);
  Serial.begin(115200);
  //delay(200);
  Serial.println("");
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  //while (!Serial) 
  //{
    //; // wait for serial port to connect. Needed for native USB port only
  //}

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

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
  
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() 
{
 // previous_time = micros();
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    //Serial.print("Received packet of size ");
    //Serial.println(packetSize);
    //Serial.print("From ");
    //IPAddress remoteIp = Udp.remoteIP();
    //Serial.print(remoteIp);
    //Serial.print(", port ");
    //Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    //Serial.println("Contents:");
    //Serial.println(packetBuffer);
    //server_command = packetBuffer;
    //Serial.println(packetBuffer);
    server_command = packetBuffer;
    if(server_command == "RB")
    {
      digitalWrite(0, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(14, LOW);
    }
    if(server_command == "RG")
    {
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      digitalWrite(14, HIGH);
    }
    if(server_command == "BG")
    {
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      digitalWrite(14, HIGH);
    }
    if(server_command == "B")
    {
      digitalWrite(0, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
    }
    else if(server_command == "R")
    {
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      digitalWrite(14, LOW);
    }
    else if(server_command == "G")
    {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(14, HIGH);
    }
    else if(server_command == "A")
    {
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(14, HIGH);
    }
    else if(server_command == "N")
    {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
      //Serial.print(loop_time);
      //Serial.println(" us");
    }

    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
  }
  //current_time = micros();
  //loop_time = current_time - previous_time;
  
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
