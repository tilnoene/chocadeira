#include <dht.h>

#define pinDHT 2

dht my_dht;

float temperature, humidity;

void setup() {
  Serial.begin(9600);
}

void loop() {
  my_dht.read11(pinDHT);
  temperature = my_dht.temperature;
  humidity = my_dht.humidity;

  Serial.print("[DHT11] Temperature: ");
  Serial.print(temperature);
  Serial.println("ºC");

  Serial.print("[DHT11] Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println();

  delay(2000);
}
