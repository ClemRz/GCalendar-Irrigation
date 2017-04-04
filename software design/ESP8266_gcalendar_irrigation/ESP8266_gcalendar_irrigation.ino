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
#include <WiFiClient.h> 
#include "FS.h"
#include "structures.h"

#define MICROSEC              1000000L
#define MILLISEC              1000L
#define SEC                   1L
#define MINUTE                (unsigned int) 60L*SEC
#define HOUR                  (unsigned int) 60L*MINUTE
#define DAY                   (unsigned long) 24L*HOUR

#define DEBUG                 1

#define N_FAULT               4
#define CLOSE                 12
#define OPEN                  13

#define DEFAULT_WAKEUP_RATE   5*MINUTE
#define CONFIG_FILE_PATH      "/cfg.json"

#define VERSION               "1.0"



void setup() {
#if DEBUG
  initSerial();
#endif
  initIO();
  initFS();
  openValve();
  delay(2 * MILLISEC);
  closeValve();
  sleep();
}

void loop() {
}

void sleep(void) {
#if DEBUG
  Serial.print(F("Go to sleep for "));
  //Serial.print(_wakeupRate * MICROSEC);
  Serial.println(F("us."));
#endif  //DEBUG
  ESP.deepSleep(0); //_wakeupRate * MICROSEC);
}

