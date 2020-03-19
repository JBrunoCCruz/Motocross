#include "SPIFFS.h"
#include <BluetoothSerial.h>
#include <WiFi.h>
#include <Events.h>
#include <EventQueue.h>
#include <EventDispatcher.h>

// let's suppose we have three pushbuttons
// A, B and C connected to digital pins 5, 3, 4
#define NUM_KEYS 3
#define KEY_A 1
#define KEY_B 2
#define KEY_C 3
#define buttonPinInc KEY_A 
#define buttonPinDec KEY_B 
#define buttonPinOk KEY_C 
// int kb_pins[NUM_KEYS] = { 5, 3, 4 };
int kb_pins[NUM_KEYS] = { 5, 15, 4 };
int kb_keys[NUM_KEYS] = { KEY_A, KEY_B, KEY_C };
int kb_on[NUM_KEYS] = { 0, 0, 0 };
int kb_off[NUM_KEYS] = { 0, 0, 0 };
int kb_curr_state[NUM_KEYS] = { 0, 0, 0 };
int kb_prev_state[NUM_KEYS] = { 0, 0, 0 };
#define KB_SAMPLE_DELAY 10
#define KB_DEBOUNCE_COUNT 3

// led to be turned on or off
#define LED_PIN 23

// Bluetooth object
BluetoothSerial SerialBT;
// the event queue
EventQueue q;
// the event dispatcher
EventDispatcher disp (&q);

void scanwifi (void);
void conexaobluetooth (void);
void recordflashmemory (void);
void timeHandler (int event, int param);
void kbHandler (int event, int param);
void timeManager (void);
void kbManager (void);

void setup() {
  Serial.begin (9600); // 3 RX - 1 RX (UART 0)
  Serial2.begin (9600); // 16 RX - 17 TX (UART 1)
  Serial.println ("LIT - IFCE");

  SerialBT.begin ("ESP32_LIT");
  Serial.println ("Bluetooth iniciado! Pronto para parear!");

  WiFi.mode (WIFI_STA);
  WiFi.disconnect ();
  delay (100);
  Serial.println ("Configuracao do Wi-Fi concluida!");

  pinMode (KEY_A, INPUT);
  pinMode (KEY_B, INPUT);
  pinMode (KEY_C, INPUT);
  pinMode (LED_PIN, OUTPUT);
  
  // call kbHandler for _both_ KEY_PRESS and KEY_RELEASE events
  disp.addEventListener (Events::EV_KEY_PRESS, kbHandler);
  disp.addEventListener (Events::EV_KEY_RELEASE, kbHandler);
}

void loop() {
  // call the event generating functions
   kbManager ();

   // get events from the queue and call the
   // registered function(s)
   disp.run ();
}

// time event handler
void timeHandler (int event, int param) {
   Serial.print ("Time elapsed: ");
   Serial.println (millis () / 1000);
}

// keyboard event handler
void kbHandler (int event, int param) {
   switch (event) {
       case Events::EV_KEY_PRESS:
           Serial.print ("key pressed: ");
           if (param == KEY_B) {
               digitalWrite (LED_PIN, 1);    // key B turns the led ON
               SerialBT.print (1);                
           } else if (param == KEY_C) {
               SerialBT.print (2); 
           } else if (param == KEY_A) {
               SerialBT.print (3);
           }
           break;
       
       case Events::EV_KEY_RELEASE:
           Serial.print ("key released: ");
           if (param == KEY_C) {
               digitalWrite (LED_PIN, 0);    // key C turns the led OFF               
           }
           break;
   }
   
   switch (param) {
       case KEY_A:
           Serial.print ("A");
           break;
       
       case KEY_B:
           Serial.print ("B");
           break;
       
       case KEY_C:
           Serial.print ("C");
           break;
   }
   
   Serial.println ();
}


// this function generates an EV_TIME event
// each 1000 ms
void timeManager () {
   static unsigned long prevMillis = 0;
   unsigned long currMillis;

   currMillis = millis ();
   if (currMillis - prevMillis >= 1000) {
       prevMillis = currMillis;
       q.enqueueEvent (Events::EV_TIME, 0);    // param is not used here
   }
}


// this function debounces the pushbutton pins
// and emits the "keyboard events"
void kbManager () {
   static unsigned long prevMillis = 0;
   unsigned long currMillis;
   int i;
   
   currMillis = millis ();
   if (currMillis - prevMillis >= KB_SAMPLE_DELAY) {
       prevMillis = currMillis;
       for (i = 0; i < NUM_KEYS; i++) {
           if ( ! digitalRead (kb_pins[i])) {    // buttons are active low
               kb_on[i]++;
               kb_off[i] = 0;
           }
           else {
               kb_on[i] = 0;
               kb_off[i]++;
           }
           
           if (kb_on[i] >= KB_DEBOUNCE_COUNT) {
               kb_on[i] = 0;
               kb_off[i] = 0;
               kb_curr_state[i] = 1;
               if (kb_prev_state[i] == 0) {
                   // it was released and now it's pressed
                   kb_prev_state[i] = 1;
                   q.enqueueEvent (Events::EV_KEY_PRESS, kb_keys[i]);
               }
           }
           
           if (kb_off[i] >= KB_DEBOUNCE_COUNT) {
               kb_on[i] = 0;
               kb_off[i] = 0;
               kb_curr_state[i] = 0;
               if (kb_prev_state[i] == 1) {
                   // it was pressed and now it's released
                   kb_prev_state[i] = 0;
                   q.enqueueEvent (Events::EV_KEY_RELEASE, kb_keys[i]);
               }
           }
       }
   }
}
