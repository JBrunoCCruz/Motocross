#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin (115200);
  SerialBT.begin ("ESP32_LIT"); //Bluetooth device name
  Serial.println ("Dispositivo iniciado! Pronto para parear.");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
