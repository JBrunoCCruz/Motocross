#include "FS.h"
#include "SPIFFS.h"

#define FORMAT_SPIFFS_IF_FAILED true

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
  }
  
  File file = SPIFFS.open("/test.txt", FILE_WRITE);

  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  if (file.print("TEST")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
