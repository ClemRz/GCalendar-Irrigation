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
    along with GCalendarIrrigation.  If not, see <http://www.gnu.org/licenses/>.
 */

void initWiFi(void) {
#if DEBUG
  Serial.println(F("Start WiFi"));
#endif
  WiFi.persistent(true);
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED && _attempts <= MAX_WIFI_ATTEMPTS) {
      delay(500);
#if DEBUG
      Serial.print(F("."));
#endif
      _attempts++;
    }
  }
#if DEBUG
  Serial.println();
  if (_attempts > MAX_WIFI_ATTEMPTS) {
    Serial.print(F("Failed to connect to "));
    Serial.println(SSID);
  } else {
    Serial.print(F("Connected to "));
    Serial.println(SSID);
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
    Serial.print(F("Mac addresss: "));
    Serial.println(WiFi.macAddress());
  }
#endif
}
