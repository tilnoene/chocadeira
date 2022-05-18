#include <Wire.h>

#define pinRelay1 7
#define pinRelay2 8

bool lampState;

void setup() {
  Serial.begin(9600);

  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);

  lampState = false;
  digitalWrite(pinRelay1, HIGH);
  digitalWrite(pinRelay2, HIGH);
}

void loop() {
  if (lampState) {
    Serial.println("[RELAY] Light ON");

    digitalWrite(pinRelay1, LOW);
    digitalWrite(pinRelay2, LOW);
  } else {
    Serial.println("[RELAY] Light OFF");
    
    digitalWrite(pinRelay1, HIGH);
    digitalWrite(pinRelay2, HIGH);
  }

  lampState = !lampState;
  delay(1000);
}
