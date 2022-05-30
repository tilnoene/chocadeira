#include <dht.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

/* custom characters LCD */

byte degree[8] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte gout[8] = {
  B00100,
  B01010,
  B10001,
  B10001,
  B11011,
  B11111,
  B01110,
  B00000
};

byte thermometer[8] = {
  B01110,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110,
  B00000
};

byte light_off[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10101,
  B01110,
  B01110,
  B00100
};

byte light_on[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B00100
};

// brooder settings
float minTemperature = 36.0;
float temperatureError = -1.0; // adjust sensor temperature error

#define pinDHT 2
#define pinRelay 7
#define debugMode true // print on serial monitor

dht my_dht;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void displayLCD();
void EEPROMClear();
void EEPROMWriteInt(int address, int value); // write 2 bytes
int EEPROMReadInt(int address);

int qntSeconds;
float temperature, humidity;
bool lampState;

void setup() {
  if (debugMode) {
    Serial.begin(9600);
    Serial.println("Booting...");
  }
  
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.createChar(1, gout);
  lcd.createChar(2, thermometer);
  lcd.createChar(3, light_off);
  lcd.createChar(4, light_on);
  lcd.clear();

  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");

  pinMode(pinRelay, OUTPUT);

  digitalWrite(pinRelay, HIGH);

  lampState = true;

  // EEPROMClear();

  delay(1000);
  lcd.clear();
}

void loop() {
  my_dht.read11(pinDHT);
  temperature = my_dht.temperature + temperatureError;
  humidity = my_dht.humidity;

  displayLCD();

  // if the temperature is lower than minTemperature, turn on the relay for a few seconds
  if (temperature <= minTemperature) {
    digitalWrite(pinRelay, LOW);
    
    delay(3000);

    displayLCD();
    digitalWrite(pinRelay, HIGH);

    delay(15000);

    displayLCD();
  }
  
  if (debugMode) {
    debugData();
  }

  delay(2000);
}

void debugData() {
  // status code (only temperature)
  if (temperature < 36) {
    Serial.print("[02] ");
  } else if (temperature > 38) {
    Serial.print("[03] ");
  } else {
    Serial.print("[00] ");
  }

  // data info
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.println();
}

/* LCD Display */

void displayLCD() {
  // display basic info
  lcd.setCursor(0, 0);
  lcd.write(byte(2)); // thermomether
  lcd.setCursor(1, 0);
  lcd.print(27);
  lcd.setCursor(3, 0);
  lcd.write(byte(0)); // degree
  lcd.setCursor(4, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.write(byte(1)); // gout
  lcd.setCursor(1, 1);
  lcd.print(80);
  lcd.print("%");

  if (lampState) {
    lcd.setCursor(15, 0);
    lcd.write(byte(4)); // light on
    lcd.setCursor(11, 0);
    lcd.print("LIG");
  } else {
    lcd.setCursor(15, 0);
    lcd.write(byte(3)); // light off
    lcd.setCursor(11, 0);
    lcd.print("DES");
  }
}

/* EEPROM */

void EEPROMClear() {
  for (int i = 0; i < 1000; i++) { 
    EEPROM.write(i, 0);
  }
}

void EEPROMWriteInt(int address, int value){
  byte hiByte = highByte(value);
  byte loByte = lowByte(value);

  EEPROM.write(address, hiByte);
  EEPROM.write(address + 1, loByte);   
}

int EEPROMReadInt(int address){
  byte hiByte = EEPROM.read(address);
  byte loByte = EEPROM.read(address + 1);
  
  return word(hiByte, loByte); 
}
