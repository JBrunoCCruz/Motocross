//#include <SoftwareSerial.h>
#include "HardwareSerial.h"
#include <TinyGPS++.h>

//SoftwareSerial gpsSerial (16, 17);

HardwareSerial SerialGPS(1);

TinyGPSPlus gps;

struct GpsDataState_t {
  double originLat = 0;
  double originLon = 0;
  double originAlt = 0;
  double distMax = 0;
  double dist = 0;
  double altMax = -999999;
  double altMin = 999999;
  double spdMax = 0;
  double prevDist = 0;
};
GpsDataState_t gpsState = {};

#define TASK_SERIAL_RATE 1000 // ms
uint32_t nextSerialTaskTs = 0;
uint32_t nextOledTaskTs = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //gpsSerial.begin (9600);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (gpsSerial.available ()) {
//    Serial.print (gpsSerial.read ());
//  }
  gpsState.originLat = gps.location.lat();
  gpsState.originLon = gps.location.lng();
  gpsState.originAlt = gps.altitude.meters();

  gpsState.distMax = 0;
  gpsState.altMax = -999999;
  gpsState.spdMax = 0;
  gpsState.altMin = 999999;

  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }
 
  /*
     Damit nicht zu viele Daten im Serial Monitor ausgegeben werden,
     beschränken wir die Ausgabe auf die Anzahl Millisekunden
     die wir in der Konstante "TASK_SERIAL_RATE" gespeichert haben
  */
  if (nextSerialTaskTs < millis()) {
    Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
    Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
    Serial.print("ALT=");  Serial.println(gps.altitude.meters());
    Serial.print("Sats=");  Serial.println(gps.satellites.value());
    Serial.print("DST: ");
    Serial.println(gpsState.dist, 1);
    nextSerialTaskTs = millis() + TASK_SERIAL_RATE;
  }
  
}
