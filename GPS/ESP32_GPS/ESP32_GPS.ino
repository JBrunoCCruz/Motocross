#include <SoftwareSerial.h>
#include "GPS_Moto.h"
#include "string.h"
#include "BluetoothSerial.h"

dataGPS dadosDoGPS;

SoftwareSerial gpsSerial (16, 17); //RX - TX
BluetoothSerial SerialBT; // Objeto bluetooth

void adquirirDadosDoGPS (void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  gpsSerial.begin (9600);

  SerialBT.begin ("ESP32_LIT"); //Bluetooth device name
  Serial.println ("Dispositivo iniciado! Pronto para parear!");
}

void loop() {
  // put your main code here, to run repeatedly:
  adquirirDadosDoGPS ();
}

void adquirirDadosDoGPS (void) {
    char c;
    char cDataBuffer[100], *ponteiroProBuffer;
    ponteiroProBuffer = cDataBuffer;
    int verificacao = 0, i, contLat = 0, contLon = 0;
    int latitudeBluetooth, longitudeBluetooth;
    int latitudeBluetoothVetor[4], longitudeBluetoothVetor[4];
    while (true) {
        if (gpsSerial.available ()) {
            c = gpsSerial.read();
            if (c == '$') { // Espera um $ (Identifica o inicio de um mensagem)
                for (i = 0; i < sizeof (cDataBuffer); ) {
                    if (gpsSerial.available ()) {
                        c = gpsSerial.read();
                        if (c == '\r' ) {
                            verificacao = parse (ponteiroProBuffer, &dadosDoGPS);                            
                            i = sizeof (cDataBuffer);                                                    
                        } else {
                            cDataBuffer[i++] = c;                        
                        }                        
                    }                                   
                }
            }                                           
        }
        
        latitudeBluetooth = dadosDoGPS.latitude * 100;        
        while ( (latitudeBluetooth % 10) != 0 ) {
            latitudeBluetoothVetor[contLat++] = latitudeBluetooth % 10;
            latitudeBluetooth /= 10;
        }
        longitudeBluetooth = dadosDoGPS.longitude * 100;
        while ( (longitudeBluetooth % 10) != 0 ) {
            longitudeBluetoothVetor[contLon++] = longitudeBluetooth % 10;
            longitudeBluetooth /= 10;
        }

        
        while (contLat >= 0) {
          //SerialBT.write ( (latitudeBluetoothVetor[contLat--]) + 48);
          Serial.print (latitudeBluetoothVetor[contLat--]);
          delay (2);
        }
        delay (50);
        //SerialBT.write (' ');
        Serial.print (' ');
        while (contLon >= 0) {
          //SerialBT.write ( (longitudeBluetoothVetor[contLon--]) + 48);
          Serial.print (longitudeBluetoothVetor[contLon--]);
          delay (2);
        }
        //SerialBT.write (' ');
        Serial.print (' ');
        delay (50);
          
    }
    return;
}
