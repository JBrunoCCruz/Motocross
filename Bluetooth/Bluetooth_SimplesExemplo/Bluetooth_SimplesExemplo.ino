#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int i = 0;
char lido;

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
    lido = SerialBT.read ();
    if (lido == '-' && i > 0) {
      Serial.print ("Diminuir - ");
      i--;  
    } else if (lido == '+' && i < 10) {
      Serial.print ("Aumentar - ");
      i++;
    }
    Serial.print ("Volume: ");
    Serial.println (i);
  }
  
  delay(20);
}
