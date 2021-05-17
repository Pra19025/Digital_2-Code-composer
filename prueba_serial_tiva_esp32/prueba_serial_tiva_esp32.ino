String datos = "";
String p1;
String p2;
String p3;
String p4;


void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
  Serial.begin(115200);

}

void loop() {
  //Serial.println("prueba");
  // put your main code here, to run repeatedly:
  while (Serial2.available()) {
    char lectura = Serial2.read();
    if (lectura != '\n') {
      datos.concat(lectura);
    } else {

      p1 = getValue(datos, ',', 0);
      p2 = getValue(datos, ',', 1);
      p3 = getValue(datos, ',', 2);
      p4 = getValue(datos, ',', 3);

      Serial.print(p1);
      Serial.print(p2);
      Serial.print(p3);
      Serial.print(p4[0]);
      Serial.print('\n');
      

      datos = "";

    }

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
