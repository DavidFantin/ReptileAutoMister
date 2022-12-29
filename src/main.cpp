/*
* Hardware: Arduino Nano (ATmega328)
* Author: David Fantin
* Date created: 12/28/2022
* Last update: 12/29/2022
*/

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define SPRAY 12

DHT dht(DHTPIN, DHTTYPE);
double idealHumi = 40;

void setup() {
   Serial.begin(9600);
   pinMode(SPRAY, OUTPUT);
   dht.begin();
}

void loop() {
   // delay between measurments
   delay(2000);

   // read humidity
   float humi  = dht.readHumidity();

   // check if any read failed
   if (isnan(humi)) {
      Serial.println("Failed to read from DHT sensor!");
   } else {
      Serial.print("Humidity: ");
      Serial.print(humi);
      Serial.print("%");

      // if humidity is under the ideal percentage, start the spray sequence
      if (humi < idealHumi) {
         // spray sequence
         digitalWrite(SPRAY, HIGH);
         delay(10000);
         digitalWrite(SPRAY, LOW);
      }
   }
}
