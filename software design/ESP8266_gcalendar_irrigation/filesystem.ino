/*
    Copyright (C) 2017 Clément Ronzon

    This file is part of GCalendarIrrigation.

    GCalendarIrrigation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GCalendarIrrigation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GCalendarIrrigation.  If not, see <http://www.gnu.org/licenses/>.
 */

 void readOfflineTime(void) {
  File file = SPIFFS.open(CONFIG_FILE_PATH, "r");
  if (file) {
    while(file.available()) {
      _offlineTime = file.readStringUntil('\n').toInt();
    }
    file.close();
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif
  }
}

void writeOfflineTime(void) {
  File file = SPIFFS.open(CONFIG_FILE_PATH, "w");
  if (file) {
    file.println(_offlineTime);
    file.close();
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif
  }
}

