/*
   Created by nurullah Sadekeen
   Email: nurullahsadekin@gmail.com
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"	// Install Firebase ESP8266 library
#include <ESP8266WiFi.h>	// Install DHT11 Library and Adafruit Unified Sensor Library


#define FIREBASE_HOST "fir-iot-c6f4c.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "5z9Mz5pyxgSnnbfwDil7f9qGZzCbZt8zu3kgOmWF"
#define WIFI_SSID "eub"
#define WIFI_PASSWORD "eubsixteen"

//#define DHTPIN 2		// Connect Data pin of DHT to D2
int flame_detected;
int led = D0;	// Connect LED to D4
int led2 = D1;
int led3 = D2;
int tankpump = D3;
int firepump = D9;
int flame_sensor = D6;
int PIR = D7;
int full = D8;
int low = D5; 
// Connect LED to D5

//#define DHTTYPE    DHT11
//DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseData led2Data;

FirebaseJson json;


void setup()
{

  //Serial.begin(115200);

  //dht.begin();
    pinMode(led,OUTPUT);
    pinMode(led2,OUTPUT);
     pinMode(led3,OUTPUT);
      pinMode(firepump,OUTPUT);
       pinMode(tankpump,OUTPUT);
        pinMode(flame_sensor,INPUT);
         pinMode(PIR,INPUT);
          pinMode(full,INPUT);
           pinMode(low,INPUT);
           digitalWrite(firepump,LOW);
           digitalWrite(tankpump,LOW);
           digitalWrite(led3,LOW);
           digitalWrite(led,LOW);
           digitalWrite(led2,LOW);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print(".");
    delay(300);
  }
  //Serial.println();
  //Serial.print("Connected with IP: ");
  //Serial.println(WiFi.localIP());
  //Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
void loop() {
  if ((Firebase.getString(ledData, "/FirebaseIOT/led"))&&(Firebase.getString(led2Data, "/FirebaseIOT/led2"))){
   //Serial.println(ledData.stringData());
    if (ledData.stringData() == "0") {
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "1"){
    digitalWrite(led, LOW);
    }
    if (led2Data.stringData() == "0") {
    digitalWrite(led2, HIGH);
    }
  else if (led2Data.stringData() == "1"){
    digitalWrite(led2, LOW);
    }
  }
  ////////////////////Motion Detection//////////////////////////////// 
  if (digitalRead (PIR) == HIGH)
 {
  digitalWrite (led3,HIGH);
  }
else {
    digitalWrite (led3,LOW);
  }
 //////////////////////////////////Flame/////////////////////////////
 flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 0)
  {
    //Serial.println("Flame detected...! take action immediately.");
    digitalWrite(firepump, HIGH);
    delay(10000);
  }
  else
  {
    //Serial.println("No flame detected. stay cool");
    digitalWrite(firepump, LOW);
  }
  /////////////////////////////////////Tank//////////////////////////////////
   if (digitalRead(full) == LOW && digitalRead(low) == LOW)
  {
    digitalWrite(tankpump, HIGH);
    }
    else if(digitalRead(full) == HIGH && digitalRead(low) == HIGH) {
  digitalWrite(tankpump, LOW);
  }
}
