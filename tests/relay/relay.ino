#include <Wire.h>

#define pinRelay1 7

bool lampState;

void setup() {
  Serial.begin(9600);

  pinMode(pinRelay1, OUTPUT);

  lampState = false;
  digitalWrite(pinRelay1, HIGH);
}

void loop() {
  if (lampState) {
    Serial.println("[RELAY] Light ON");

    digitalWrite(pinRelay1, LOW);
  } else {
    Serial.println("[RELAY] Light OFF");
    
    digitalWrite(pinRelay1, HIGH);
  }

  lampState = !lampState;
  delay(1000);
}
