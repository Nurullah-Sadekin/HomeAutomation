int LED = D5;
int flame_sensor = D6;
int flame_detected;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop()
{
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(LED, HIGH);
    delay(6000);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(LED, LOW);
  }
  delay(1000);
}
