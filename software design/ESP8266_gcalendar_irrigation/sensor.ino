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

void readSensor(void) {
  _sensorExists = _sensor.sensorExists();
  if (_sensorExists) {
    _celsiusHundredths = _sensor.getCelsiusHundredths();
    _humidityPercent = _sensor.getHumidityPercent();
    #if DEBUG
    printSensor();
    #endif  //DEBUG
  } else {
    #if DEBUG
    Serial.println(F("Sensor error"));
    #endif  //DEBUG
  }
}

void printSensor(void) {
  Serial.println(F("Sensors: "));
  printValues(_celsiusHundredths, _humidityPercent);
}

void printValues(int celsiusHundredths, int humidityPercent) {
  Serial.print(F("Temperature: ")); Serial.print(celsiusHundredths * 0.01); Serial.println(F("C hundredths"));
  Serial.print(F("Humidity: ")); Serial.print(humidityPercent * 0.01); Serial.println(F("%RH"));
  Serial.println();
}
