
void setup()
{
  Serial.begin(9600);
  pinMode(D8, INPUT );
   pinMode(D4, INPUT);
   pinMode(D3 , OUTPUT);
   
}
void loop()
{
if (digitalRead(D8) == HIGH && digitalRead(D4) == HIGH) {
  digitalWrite(D3, HIGH);
} else if (digitalRead(D8) == LOW && digitalRead(D4) == LOW) {
   digitalWrite(D3, LOW);
}
else{digitalWrite(D3, LOW);}
}
