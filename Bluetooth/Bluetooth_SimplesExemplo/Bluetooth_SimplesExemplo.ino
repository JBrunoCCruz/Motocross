#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int i = 0, cont = 1;
char lido[5];

void setup() {
  Serial.begin (115200);
  SerialBT.begin ("ESP32_LIT"); //Bluetooth device name
  Serial.println ("Dispositivo iniciado! Pronto para parear!");
}

void loop() {
  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  if (SerialBT.available()) {
    lido[0] = SerialBT.read ();
    while (lido[0] != '#') {
      lido[0] = SerialBT.read ();
    }
    do {
      lido[cont] = SerialBT.read ();
    } while (lido[cont++] != '#');
      
  }
  
  
  delay(20);
}
