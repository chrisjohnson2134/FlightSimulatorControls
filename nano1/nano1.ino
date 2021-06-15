#include <Wire.h>
#include "Message.h"

dataMessage messageData;
bool intiated = false;

void setup() {
  Wire.begin(8);                
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);
  messageData.status = 2;
  messageData.buttons = 3; //number of buttons on device (binary) 0x11 ,2 btns

  pinMode(2, INPUT);
  pinMode(4, INPUT);

}

void loop() {
  
  int a = digitalRead(2);
  int b = digitalRead(4);
  messageData.buttons |= b << 1;
//  Serial.println(messageData.buttons);
}


void requestEvent() {
  Wire.write((byte *)&messageData,sizeof messageData); 
  intiated = true;
}
