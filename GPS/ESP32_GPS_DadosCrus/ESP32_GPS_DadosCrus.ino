// Inclusão da biblioteca para manipulação da Serial
#include <SoftwareSerial.h>

// Criação do objeto para obter os dados fornecidos pelo GPS na serial
SoftwareSerial gpsSerial (16, 17);

void setup() {
  // put your setup code here, to run once:
  // Serial da ESP32 com Computador - Taxa de transmissão igual a 115200 bps
  Serial.begin (115200);

  // Serial da ESP32 com GPS - Taxa de transmissão igual a 9600 bps
  gpsSerial.begin (9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  // Verifica se é verdade que há algum dado sendo enviado pelo GPS na serial
  if (gpsSerial.available ()) {
    // Mostrado o dado lido da serial
    Serial.write (gpsSerial.read ());
  }
}
