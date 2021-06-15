#include <Wire.h>
#include "Message.h"

dataMessage messageData;

void setup() {
  Wire.begin(9);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);
  messageData.status = 2;

  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  int a = digitalRead(2);
  messageData.buttons = a;
  int b = digitalRead(3);
  messageData.buttons |= b << 1;
  Serial.println(messageData.buttons);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write((byte *)&messageData,sizeof messageData); 
}
