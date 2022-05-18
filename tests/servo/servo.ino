#include <Servo.h>

#define pinServo1 9
#define pinServo2 10

Servo servo;

void rotateMotors(bool increase);

bool motorDirection; // false => 0º to 180º, true => 180º to 0º

void setup() {
  motorDirection = false;
}

void loop() {
  rotateMotors(motorDirection);
  motorDirection = !motorDirection;
  delay(1000);
}

void rotateMotors(bool increase) {
  servo.attach(pinServo1);
  digitalWrite(pinServo2, HIGH);

  if (increase) {
    // 0 to 180 degrees
    for (int i = 0; i <= 180; i++) {
      servo.write(i);
      delay(10);
    }
  } else {
    // 180 to 0 degrees
    for (int i = 180; i >= 0; i--){
      servo.write(i);
      delay(10);
    }
  }

  digitalWrite(pinServo2, LOW);
}
