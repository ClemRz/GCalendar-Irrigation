/*
    Copyright (C) 2017 Clément Ronzon

    This file is part of EspDataLogger.

    SpotPipe is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GCalendarIrrigation.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 void openValve(void) {
  actuateValve(true);
}

void closeValve(void) {
  actuateValve(false);
}

void actuateValve(bool openValve) {
#if DEBUG
  Serial.print(openValve ? F("Open") : F("Close")); Serial.println(F(" the valve."));
#endif
  int pin = openValve ? OPEN : CLOSE;
  digitalWrite(pin, HIGH);
  delay(5);
  lookForFault();
  delay(5);
  digitalWrite(pin, LOW);
}

void lookForFault(void) {
  bool isInFault = digitalRead(N_FAULT) == LOW;
#if DEBUG
  if (isInFault) {
    Serial.println(F("Driver is showing a fault"));
  }
#endif
}

