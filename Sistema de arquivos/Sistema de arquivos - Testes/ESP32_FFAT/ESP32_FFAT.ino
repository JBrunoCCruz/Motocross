#include "FFat.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);

  //Mounting File Systtem
  if (! FFat.begin (true)) {
    Serial.println ("Mounted Failed");  
    return;
  }
  Serial.println ("File system mounted");

  //Create a file and writing
  /*File file = FFat.open ("/testfat.txt", FILE_WRITE);
  if (!file) {
    Serial.println ("There waas an error opening the file for writing.");
    return;
  }
  
  if (file.print ("TEST")) {
    Serial.println ("File was writeen.");
  } else {
    Serial.println ("File writen failed.");
  }
  file.close ();*/

  //Appeding a conteente to file
  /*File file3  = FFat.open ("/testfat.txt", FILE_APPEND);
  if (! file3) {
    Serial.println ("There was an error opening the file for appeding.");
    return;
  }

  if (file3.println ("Novo conteudo")) {
    Serial.println ("Content was appended.");
  } else {
    Serial.println ("File append failed.");
  }
  file3.close ();*/

  //Opening a file and reading
  /*File file2 = FFat.open ("/testfat.txt", FILE_READ);
  if (!file2) {
    Serial.println ("There was an error opening the file for writing.");
    return;
  }

  Serial.print ("File Content: ");
  while (file2.available ()) {
    Serial.write (file2.read ());
  }

  if (FFat.remove ("/testfat.txt"))
    Serial.println ("Sucesso em remover!");
  
  file2.close ();*/

 

  //Verify if file exists
  Serial.println (FFat.exists("/testfat.txt"));
  Serial.println (FFat.exists("/nonexisting.txt"));

  Serial.println (FFat.totalBytes ());
  Serial.println (FFat.freeBytes ());

}

void loop() {
  // put your main code here, to run repeatedly:

}
