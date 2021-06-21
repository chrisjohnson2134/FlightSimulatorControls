#include <Wire.h>
#include "Message.h"

dataMessage messageData;
bool intiated = false;

void setup() {
  Wire.begin(4);                
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);
  messageData.status = 2;
  messageData.numButtons = 2; //number of buttons on device (binary) 0x11 ,2 btns
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  Serial.println("Startup Complete");

}

void loop() {
  if(!intiated)
    return;
    
  int a = digitalRead(2);
  int b = digitalRead(3);
  messageData.buttons = a;
  messageData.buttons |= b << 1;
  messageData.zAxis = analogRead(A1);
  Serial.println(messageData.zAxis);
//  Serial.println(messageData.buttons);
}

void requestEvent() {
  Wire.write((byte *)&messageData,sizeof messageData); 
  if(!intiated)
   {
      delay(100);
      intiated = true;
   }
}
