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

void initSerial(void) {
  Serial.begin(9600);
  Serial.println();
  //Serial.setDebugOutput(true);
}

void initIO(void) {
  pinMode(N_FAULT, INPUT_PULLUP);
  pinMode(OPEN, OUTPUT);
  pinMode(CLOSE, OUTPUT);
}

