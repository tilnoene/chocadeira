#include <DS3231.h>

DS3231 clock;

int hours, minutes, seconds, year, month, day;
float temperatureRTC;

void setup() {
  Serial.begin(9600);
  clock.begin();
  
  Serial.println("Booting...");

  // update RTC date and time (Year, Month, Day, Hour, Minute, Second)
  // clock.setDateTime(2022, 5, 17, 21, 19, 0);
}

void loop() {
  year = clock.getDateTime().year;
  month = clock.getDateTime().month;
  day = clock.getDateTime().day;

  hours = clock.getDateTime().hour;
  minutes = clock.getDateTime().minute;
  seconds = clock.getDateTime().second;

  temperatureRTC = clock.readTemperature();

  Serial.print("[RTC] Year: ");
  Serial.println(year);
  Serial.print("[RTC] Month: ");
  Serial.println(month);
  Serial.print("[RTC] Day: ");
  Serial.println(day);

  Serial.print("[RTC] Hours: ");
  Serial.println(hours);
  Serial.print("[RTC] Minutes: ");
  Serial.println(minutes);
  Serial.print("[RTC] Seconds: ");
  Serial.println(seconds);

  Serial.print("[RTC] Temperature: ");
  Serial.println(temperatureRTC);
  
  Serial.println();

  delay(1000);
}
