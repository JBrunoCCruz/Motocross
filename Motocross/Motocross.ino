#include <SoftwareSerial.h>
#include "SPIFFS.h"
#include <BluetoothSerial.h>
#include <WiFi.h>

// Objetos (UART, Bluetooth, Wifi)
SoftwareSerial gpsSerial (16, 17); //RX - TX
BluetoothSerial SerialBT;

// Variáveis Ficticias utilizadas para testes
float latitudeFicticia = -3.5, longitudeFicticia = -38.7;
char NMEAFicticio[] = {'G', 'N', 'R', 'M', 'C', '\0'};
char Empresa[] = {'L', 'I', 'T', '\0'};

void setup() {
  Serial.begin (115200);
  Serial.println ("LIT - IFCE");

  SerialBT.begin ("ESP32_LIT");
  Serial.println ("Bluetooth iniciado! Pronto para parear!");

  WiFi.mode (WIFI_STA);
  WiFi.disconnect ();
  delay (100);
  Serial.println ("Configuracao do Wi-Fi concluida!");
}

void scanwifi ();
void conexaobluetooth ();
void recordflashmemory ();

void loop() {
  
}
