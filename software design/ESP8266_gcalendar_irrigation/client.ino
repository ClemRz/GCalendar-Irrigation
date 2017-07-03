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
String httpsGet(void) {
  HTTPSRedirect* client = new HTTPSRedirect(HTTPS_PORT);
  bool connected = false;
  for (int i=0; i<MAX_HTTPS_ATTEMPTS; i++){
    yield();
    int retval = client->connect(HOST, HTTPS_PORT);
    if (retval == 1) {
       connected = true;
       break;
#if DEBUG
    } else {
      Serial.println(F("Connection failed. Retrying..."));
#endif
    }
    delay(HTTPS_REINTENT_DELAY*MILLISEC);
  }

  if (!connected) {
#if DEBUG
    Serial.print(F("Could not connect to server"));
#endif
    return "";
  }
  
  if (client->GET(URL, HOST)) {
    String payload = client->getResponseBody();
#if DEBUG
    Serial.println(F("HTTP Response: "));
    Serial.println(payload);
#endif
    if (payload.indexOf(SUCCESS) >= 0) return payload;
#if DEBUG
    Serial.print(F("Script returned failure message: ")); Serial.print(payload);
#endif
    return "";
  } else {
#if DEBUG
    Serial.print(F("Couldn't get the body, code: ")); Serial.print(client->getStatusCode()); Serial.print(F(", message: ")); Serial.println(client->getReasonPhrase());
#endif
    return "";
  }
  
  delete client;
  client = NULL;
}

