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

void initSerial(void) {
  Serial.begin(9600);
  Serial.println();
  //Serial.setDebugOutput(true);
}

void initSI7021(void) {
#if DEBUG
  Serial.println(String() + F("Initializing SI7021 over I2C (SDA: ") + String(SDA) + F(", SCL: ") + String(SCL) + F(")."));
#endif  //DEBUG
  bool ok = _sensor.begin(SDA, SCL);
#if DEBUG
  if (ok) {
    Serial.println(F("SI7021 initialized"));
  } else {
    Serial.println(F("NO SI7021 FOUND"));
  }
#endif  //DEBUG
}

void initFS(void) {
  SPIFFS.begin();
}

void initWifiAP(void) {
    WiFi.softAP(ssid);
}
void initServer(void) {
    server.on("/", HTTP_GET, handleGetRoot);
    server.on("/", HTTP_POST, handlePostRoot);
    server.begin();
}

void initPin(void) {
  pinMode(AP, INPUT_PULLUP);
  _apMode = digitalRead(AP) == LOW;
}

