#define LED (13)
uint16_t delay_time = 200;
uint32_t current_millis = 0;
uint32_t previous_millis = 0;
uint16_t delay_millis = 3000;
char inChar;

void setup() 
{
  Serial.begin(230400);
  pinMode(LED, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() 
{
  if(Serial.available() > 0)
  {
    inChar = Serial.read();
    inChar += 1;
    Serial.println(inChar);
  }

  digitalWrite(LED, LOW);
  analogWrite(11, 10);
  delay(delay_time);
  digitalWrite(LED, HIGH);
  analogWrite(11, 0);
  delay(delay_time);
  if(delay_time == 200)
  {
    delay_time = 100;
    //Serial.print("Delay Time: ");
    //Serial.println(delay_time);
  }
  else if(delay_time == 100)
  {
    delay_time = 300;
    //Serial.print("Delay Time: ");
    //Serial.println(delay_time);
  }
  else if(delay_time == 300)
  {
    delay_time = 200;
    //Serial.print("Delay Time: ");
    //Serial.println(delay_time);
  }
}
