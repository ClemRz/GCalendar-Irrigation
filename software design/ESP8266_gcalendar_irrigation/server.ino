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

void handleGetRoot(void) {
  sendWebPage(false);
}

void handlePostRoot(void) {
  int action = server.arg("action").toInt();
  _dateTime = server.arg("dt");
  switch (action) {
    case 1:
      server.sendHeader(F("Content-Disposition"), F("attachment; filename=data.csv"));
      server.sendHeader(F("Pragma"), F("no-cache"));
      sendRawFile();
      break;
    case 2:
      sendWebPage(true);
      break;
    case 3:
      _wakeupRate = server.arg("rate").toInt();
      saveWakeupRate();
      deleteData();
      ESP.restart();
      break;
    case 4:
      _wakeupRate = server.arg("rate").toInt();
      saveWakeupRate();
      sendWebPage(false);
      break;
    case 5:
      deleteData();
      sendWebPage(true);
      break;
    case 6:
      ESP.restart();
      break;
    default:
      sendWebPage(false);
  }
}

void sendRawFile(void) {
  server.send(200, F("application/csv"), retrieveRawData());
}

void sendWebPage(bool showContent) {
  readSensor();
  String out = "";
  out.concat(F("<!DOCTYPE html><html style=\"height:100%;\">"));
  out.concat(F("<head><title>ESP8266 Temp and RH Logger</title></head>"));
  out.concat(F("<bodystyle=\"height:100%;font-family:arial;\">"));
  out.concat(F("<h3>Current reading: ")); out.concat(_celsiusHundredths/100); out.concat(F("°C ")); out.concat(_humidityPercent); out.concat(F("%RH</h3>"));
  out.concat(F("<p>")); out.concat(getDataAttributes()); out.concat(F("</p>"));
  out.concat(F("<form onsubmit=\"JavaScript:var d=new Date();document.getElementById('dt').value = (d.getMonth()+1)+'/'+d.getDate()+'/'+d.getFullYear()+' '+d.getHours()+':'+d.getMinutes()+':'+d.getSeconds();return true;\" method=\"post\" style=\"height:100%;\">"));
  out.concat(F("<textarea rows=\"10\" style=\"width:50%;display:block;\" disabled>"));
  out.concat(showContent ? retrieveRawData() : F("Select \"Show file content\" to see its content here."));
  out.concat(F("</textarea>"));
  out.concat(F("<label for\"rate\">Sampling rate in seconds:</label> <input type=\"number\" min=\"1\" name=\"rate\" id=\"rate\" value=\"")); out.concat(_wakeupRate); out.concat(F("\"><br>"));
  out.concat(F("<select name=\"action\">"));
  out.concat(F("<option>-</option>"));
  out.concat(F("<option value=\"1\">Download the file</option>"));
  out.concat(F("<option value=\"2\">Show file content</option>"));
  out.concat(F("<option value=\"3\">Update rate, Delete and Reset</option>"));
  out.concat(F("<option value=\"4\">Update sampling rate</option>"));
  out.concat(F("<option value=\"5\">Delete the file</option>"));
  out.concat(F("<option value=\"6\">Reset the ESP</option>"));
  out.concat(F("</select><br>"));
  out.concat(F("<input type=\"hidden\" name=\"dt\" id=\"dt\">"));
  out.concat(F("<input type=\"submit\" value=\"Go\">"));
  out.concat(F("</form>"));
  out.concat(F("</body></html>"));
  server.send(200, F("text/html"), out);
}

