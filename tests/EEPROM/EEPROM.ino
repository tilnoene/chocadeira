#include <EEPROM.h>

#define ADDRESS_EEPROM_QNT_DAYS 1 // quantity of days elapsed
#define ADDRESS_EEPROM_QNT_SECONDS 16 // quantity of seconds elapsed
#define ADDRESS_EEPROM_MOTOR_DIRECTION 32 // direction of servo motor (false => 0º to 180º, true => 180º to 0º)

void setup() {
  Serial.begin(9600);

  // EEPROMClear(); // clear EEPROM (uncomment on first run)
}

void loop() {
  int addressValue = EEPROMReadInt(ADDRESS_EEPROM_QNT_DAYS);

  Serial.print("[EEPROM] Address ");
  Serial.print(ADDRESS_EEPROM_QNT_DAYS);
  Serial.print(" has value ");
  Serial.println(addressValue);

  EEPROMWriteInt(ADDRESS_EEPROM_QNT_DAYS, addressValue + 1); // increment the value

  delay(1000);
}

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
