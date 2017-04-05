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

#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <ArduinoJson.h>

#define MICROSEC              1000000L
#define MILLISEC              1000L
#define SEC                   1L
#define MINUTE                (unsigned int) 60L*SEC
#define HOUR                  (unsigned int) 60L*MINUTE
#define DAY                   (unsigned long) 24L*HOUR

/* 
 * ======================================
 *      User defined constants
 * ======================================
*/
#define DEFAULT_POLLING_RATE   5*MINUTE
#define SSID                  "GENERAL" //"rz_ntw"
#define PASSWORD              "LEARNFROMYESTERDAYLIVEFORTODAY" //"tortolitos"
#define SCRIPT_ID             "AKfycbxr26CjU_9MvAyYFBeOgVZiXFYdIOL-wYoGzBJdLxmXV2jkJQI"
#define DEBUG                 1
// ======================================

// Pins allocation
#define N_FAULT               4
#define CLOSE                 12
#define OPEN                  13

// HTTPS parameters
#define HTTPS_PORT            443
#define HOST                  "script.google.com"
#define URL                   "https://" HOST "/macros/s/" SCRIPT_ID "/exec"
#define SUCCESS               "\"status\":\"success\""
#define MAX_WIFI_ATTEMPTS     60
#define MAX_HTTPS_ATTEMPTS    5
#define HTTPS_REINTENT_DELAY  2*SEC

// Deep-sleep time limit
#define MAX_SLEEP_TIME        71L*MINUTE

// Global variables
HTTPSRedirect* client = NULL;
long _pollingRate = DEFAULT_POLLING_RATE;
int _attempts = 0;

void setup() {
#if DEBUG
  initSerial();
#endif
  initIO();
  initWiFi();
}

void loop() { //TODO move this in the setup?
  if (_attempts <= MAX_WIFI_ATTEMPTS) {
    _attempts = 0;
    String response = httpsGet();
    if (response != "") {
      process(response);
    } else closeValve();
  } else closeValve();
  sleep();
}

void process(String response) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(response);
  if (root.success()) {
    String status = root["status"];
    if (status == "success") {
      _pollingRate = root["data"]["nextCheckIn"];
      if (_pollingRate > MAX_SLEEP_TIME) _pollingRate = MAX_SLEEP_TIME;
      if (root["data"]["openValve"]) openValve();
      if (root["data"]["closeValve"]) closeValve();
    } else {
#if DEBUG
      Serial.print(F("Unsuccessful response: ")); Serial.println(status);
#endif
      closeValve();
    }
  } else {
#if DEBUG
    Serial.println(F("Failed to parse JSON"));
#endif
    closeValve();
  }
}

void sleep() {
#if DEBUG
  Serial.print(F("Go to sleep for "));
  Serial.print(_pollingRate);
  Serial.println(F("s."));
#endif  //DEBUG
  ESP.deepSleep(_pollingRate * MICROSEC);
}

