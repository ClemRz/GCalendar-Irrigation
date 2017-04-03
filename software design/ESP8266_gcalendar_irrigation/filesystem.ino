/*
    Copyright (C) 2016 Clément Ronzon

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
    along with EspDataLogger.  If not, see <http://www.gnu.org/licenses/>.
 */

void saveData(void) {
  File file = SPIFFS.open(DATA_FILE_PATH, "a");
  if (file) {
    file.print(millis()); file.print(F(",")); file.print(_celsiusHundredths); file.print(F(",")); file.println(_humidityPercent);
    file.close();
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif  //DEBUG
  }
}

void saveHeaders(void) {
  File file = SPIFFS.open(DATA_FILE_PATH, "a");
  if (file) {
    file.print(_dateTime); file.print(F(", rate: ")); file.print(_wakeupRate); file.print(F(", version: ")); file.println(VERSION);
    file.close();
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif  //DEBUG
  }
}

String getDataAttributes(void) {
  File file = SPIFFS.open(DATA_FILE_PATH, "r");
  String out = "";
  if (file) out.concat(F("File: ")); out.concat(file.name()); out.concat(F(" ")); out.concat(file.size()); out.concat(F("b/64kb"));
  return out;
}

void retrieveDataToSerial(void) {
  File file = SPIFFS.open(DATA_FILE_PATH, "r");
  if (!file) {
    Serial.println(F("file open failed"));
    return;
  }
  Serial.println(F("-- bof --"));
  while(file.available()) {
    Serial.println(file.readStringUntil('\n'));
  }
  Serial.println(F("-- eof --"));
}

String retrieveRawData(void) {
  File file = SPIFFS.open(DATA_FILE_PATH, "r");
  String out = "";
  if (!file) {
    out.concat(F("no data"));
  } else {
    while(file.available()) {
      out.concat(file.readStringUntil('\n')); out.concat(F("\n"));
    }
  }
  out.concat(_dateTime); out.concat(F("\n"));
  return out;
}

void deleteData(void) {
  if (SPIFFS.remove(DATA_FILE_PATH)) {
#if DEBUG
    Serial.print(DATA_FILE_PATH); Serial.println(F(" deleted"));
#endif  //DEBUG
    saveHeaders();
#if DEBUG
  } else {
    Serial.println(F("file delete failed"));
#endif  //DEBUG
  }
}

void setWakeupRate(void) {
  int rate = DEFAULT_WAKEUP_RATE;
  File file = SPIFFS.open(CONFIG_FILE_PATH, "r");
  if (file) {
    while(file.available()) {
      rate = file.readStringUntil('\n').toInt();
    }
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif  //DEBUG
  }
  _wakeupRate = rate;
}

void saveWakeupRate(void) {
  File file = SPIFFS.open(CONFIG_FILE_PATH, "w");
  if (file) {
    file.println(_wakeupRate);
    file.close();
    saveHeaders();
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif  //DEBUG
  }
}

