#include "SoftwareSerial.h"
#include "GPS_Moto.h"
#include "string.h"

dataGPS dadosDoGPS;

SoftwareSerial gpsSerial (16, 17); //RX - TX

void adquirirDadosDoGPS (void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  gpsSerial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  adquirirDadosDoGPS ();
}

void adquirirDadosDoGPS (void) {
    char c;
    char cDataBuffer[250], *ponteiroProBuffer;
    ponteiroProBuffer = cDataBuffer;
    int verificacao = 0;
    while (true) {
        if (gpsSerial.available ()) {
            c = gpsSerial.read();
            if (c == '$') { // Espera um $ (Identifica o inicio de um mensagem)
                for (int i = 0; i < sizeof (cDataBuffer); i++) {
                    c = gpsSerial.read();
                    if (c == '\r' ) {
                        verificacao = parse (ponteiroProBuffer, i, &dadosDoGPS);
                        i = sizeof (cDataBuffer);                        
                    } else {
                        cDataBuffer[i] = c;
                        if (i < 5) {
                          Serial.print (c);
                        }
                    }                
                }
            } 
        }
        Serial.println ();
        Serial.println (dadosDoGPS.latitude);
        Serial.println (dadosDoGPS.longitude);
        Serial.println ();
        delay (500);
    }
    return;
}
