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

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <SI7021.h>
#include "FS.h"
#include "structures.h"

#define MICROSEC              1000000L
#define MILLISEC              1000L
#define SEC                   1L
#define MINUTE                (unsigned int) 60L*SEC
#define HOUR                  (unsigned int) 60L*MINUTE
#define DAY                   (unsigned long) 24L*HOUR

#define AP                    4
#define SCL                   12
#define SDA                   13

#define DEFAULT_WAKEUP_RATE   10*MINUTE
#define CONFIG_FILE_PATH      "/cfg.json"
#define DATA_FILE_PATH        "/data.csv"

#define DEBUG                 0        
#define RETRIEVE              0
#define DELETE                0

#define VERSION               "1.0"

const char *ssid = "espDataLogger";
const char compile_date[] = __DATE__ " " __TIME__;

ESP8266WebServer server(80);

SI7021 _sensor;

bool _apMode = false,
     _sensorExists = false;
     
int _celsiusHundredths,
    _humidityPercent,
    _wakeupRate;

String _dateTime;

void setup() {
  initPin();
#if DEBUG || RETRIEVE || DELETE
  initSerial();
#endif  // DEBUG || RETRIEVE || DELETE
  initSI7021();
  initFS();
  setWakeupRate();
  if (_apMode) {
    startAP();
  } else {
    WiFi.mode(WIFI_OFF);
    loggData(); 
  }
}

void loop() {
  if (_apMode) server.handleClient();
}

void startAP(void) {
  initWifiAP();
  initServer();
#if DEBUG
  Serial.println(F("In AP Mode"));
#endif  // DEBUG
}

void loggData(void) {
#if RETRIEVE
  delay(5 * SEC);
  retrieveDataToSerial();
#endif //RETRIEVE
#if DELETE
  delay(5 * SEC);
  _dateTime = compile_date;
  deleteData();
#endif //DELETE
#if !RETRIEVE && !DELETE
  readSensor();
  saveData();
  sleep();
#endif  // !RETRIEVE && !DELETE
#if RETRIEVE || DELETE
  quickSleep();
#endif  // RETRIEVE || DELETE
}

void sleep(void) {
#if DEBUG
  Serial.print(F("Go to sleep for "));
  Serial.print(_wakeupRate * MICROSEC);
  Serial.println(F("us."));
#endif  //DEBUG
  ESP.deepSleep(_wakeupRate * MICROSEC);
}

void quickSleep(void) {
  Serial.print(F("Go to sleep for "));
  Serial.print(1 * MICROSEC);
  Serial.println(F("us."));
  ESP.deepSleep(1 * MICROSEC);
}

