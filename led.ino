#include "config.h"

// digital pin 16
#define BUTTON_PIN 16
#define OUTPUT_PIN 13 

// button state
bool current = false;
bool last = false;

AdafruitIO_Feed *reName = io.feed("button_new"); //New!

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT); //New!

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();

  if(digitalRead(BUTTON_PIN) == HIGH){
    current = true;
    digitalWrite(OUTPUT_PIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    current = false;
    digitalWrite(OUTPUT_PIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
  }
  if(current == last){
    return;
  }
  
  Serial.print("sending button -> ");
  Serial.println(current);

 reName->save(current); //New!

  // store last button state
  last = current;

}
