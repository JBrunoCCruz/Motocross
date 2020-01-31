#include <SoftwareSerial.h>
#include "GPS_Moto.h"
#include "string.h"

dataGPS dadosDoGPS;

SoftwareSerial gpsSerial (16, 17); //RX - TX

void adquirirDadosDoGPS (void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  gpsSerial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  adquirirDadosDoGPS ();
}

void adquirirDadosDoGPS (void) {
    char c;
    char cDataBuffer[100], *ponteiroProBuffer;
    ponteiroProBuffer = cDataBuffer;
    int verificacao = 0, i;
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
            Serial.print (dadosDoGPS.protocol);
            Serial.println ();
            verificacao = 0;
        }
    }
    return;
}
