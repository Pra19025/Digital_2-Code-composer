//Noel Prado
//19025

//Web server

//Librerías
#include <WiFi.h>
#include <WebServer.h>

//variables globales
String datos = "";
String p1;
String p2;
String p3;
String p4;

String p1disp;
String p2disp;
String p3disp;
String p4disp;

const char* ssid = "Balanya";  // Enter your SSID here
const char* password = "2016ba0000";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

uint8_t LED1pin = 2;
bool LED1status = LOW;

//configuración
void setup() {

  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  //comunicación serial con la tiva

  Serial2.begin(115200);

  pinMode(LED1pin, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);


}

void loop() {
  server.handleClient(); //para que el servidor este funcionando

  while (Serial2.available()) {

    char lectura = Serial2.read();
    if (lectura != '\n') {
      datos.concat(lectura);
    } else {

      p1 = getValue(datos, ',', 0);
      p2 = getValue(datos, ',', 1);
      p3 = getValue(datos, ',', 2);
      p4 = getValue(datos, ',', 3);

      if (p1.toInt() == 1) {
        p1disp = "Disponible";
      } else {
        p1disp = "No disponible";
      }


      if (p2.toInt() == 1) {
        p2disp = "Disponible";
      } else {
        p2disp = "No disponible";
      }


      if (p3.toInt() == 1) {
        p3disp = "Disponible";
      } else {
        p3disp = "No disponible";
      }


      if (p4.toInt() == 1) {
        p4disp = "Disponible";
      } else {
        p4disp = "No disponible";
      }



      datos = "";

    }

  }


}

//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}
//************************************************************************************************
// Handler de led1on
//************************************************************************************************
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status));
}
//************************************************************************************************
// Handler de led1off
//************************************************************************************************
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}
//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html>\n"
               "<head><meta name=\\\"viewport\\\" content=\\\"width=device-width, initial-scale=1.0, user-scalable=no\\\"\n"
               "<h1> Noel Prado </h1>\n"
               "<script>\n"
               "<!--\n"
               "function timedRefresh(timeoutPeriod) {\n"
               "\tsetTimeout(\"location.reload(true);\",timeoutPeriod);\n"
               "}\n"
               "\n"
               "window.onload = timedRefresh(1000);\n"
               "\n"
               "//   -->\n"
               "</script>"
               "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"
               "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n"
               ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n"
               ".button-on {background-color: #3498db;}\n"
               ".button-on:active {background-color: #2980b9;}\n"
               ".button-off {background-color: #34495e;}\n"
               ".button-off:active {background-color: #2c3e50;}\n"
               "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n"
               "table.blueTable {\n"
               "  border: 1px solid #1C6EA4;\n"
               "  background-color: #EEEEEE;\n"
               "  width: 100%;\n"
               "  text-align: left;\n"
               "  border-collapse: collapse;\n"
               "}\n"
               "table.blueTable td, table.blueTable th {\n"
               "  border: 1px solid #AAAAAA;\n"
               "  padding: 3px 2px;\n"
               "}\n"
               "table.blueTable tbody td {\n"
               "  font-size: 13px;\n"
               "}\n"
               "table.blueTable tr:nth-child(even) {\n"
               "  background: #D0E4F5;\n"
               "}\n"
               "table.blueTable thead {\n"
               "  background: #1C6EA4;\n"
               "  background: -moz-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  background: -webkit-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  background: linear-gradient(to bottom, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  border-bottom: 2px solid #444444;\n"
               "}\n"
               "table.blueTable thead th {\n"
               "  font-size: 15px;\n"
               "  font-weight: bold;\n"
               "  color: #FFFFFF;\n"
               "  border-left: 2px solid #D0E4F5;\n"
               "}\n"
               "table.blueTable thead th:first-child {\n"
               "  border-left: none;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "\n"
               "<table class='blueTable'>\n"
               "<thead>\n"
               "<tr>\n"
               "<th>P1</th>\n"
               "<th>P2</th>\n"
               "<th>P3</th>\n"
               "<th>P4</th>\n"
               "</tr>\n"
               "</thead>\n"
               "<tfoot>\n"
               "<tr>\n"
               "<td colspan=\"4\">&nbsp;</td>\n"
               "</tr>\n"
               "</tfoot>\n"
               "<tbody>\n"
               "<tr>\n"
               "<td>" + p1disp + "</td>\n"
               "<td>" + p2disp + "</td>\n"
               "<td>" + p3disp + "</td>\n"
               "<td>" + p4disp + "</td>\n"
               "</tr>\n"
               "</tbody>\n"
               "</table>\n"
               "<body>\n"
               "<h1> &#128664 Servidor Parqueomatic &#128664  </h1>\n"
               "";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
}



//funcion para hacer el split de la lectura serial
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
