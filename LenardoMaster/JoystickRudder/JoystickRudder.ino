#include <Joystick.h>

// Program used to test the USB Joystick object on the 
// Arduino Leonardo or Arduino Micro.

#include <Joystick.h>
#include <Wire.h>
#include "Message.h"

//dynamic struct
struct dynamicButtons {
  char address;
  char btnInput;
  bool state;
};

// Create Joystick
Joystick_ Joystick;

dynamicButtons buttonLocationArr[32];
dataMessage messageData[10];
dataMessage refMessage;

void setup() {
  Serial.begin(9600);
  
  Joystick.begin();  

  Wire.begin();        // join i2c bus (address optional for master)

  setupButtonMap();
  
  }


void loop() {

  int capture = 0;

//    Joystick.setButton(2,messageData.buttons & (1));
//    Joystick.setButton(3,messageData.buttons & (1 << 1));

  Serial.println("request1");

  Wire.requestFrom(8, sizeof refMessage);
  while (Wire.available()) { // slave may send less than requested
     Wire.readBytes((byte *) &refMessage,sizeof refMessage); // receive a byte as character
  }
  Serial.println(refMessage.buttons);
  
   delay(1000);
  
  Joystick.sendState();
    
}

void setupButtonMap(){
  int i = 1,j = 0,btnPosition = 0;

  for(i =  1; i <= 10; i++)//create timeout to get up to X devices
  {
    for(j = 0; j < 32; j++)
    {
      Wire.requestFrom(i, sizeof refMessage);
      while (Wire.available()) { // slave may send less than requested
        Wire.readBytes((byte *) &refMessage,sizeof refMessage); // receive a byte as character
      }
      
      if(refMessage.buttons & (1 << j))
      {
        buttonLocationArr[j].address = i;
        buttonLocationArr[j].btnInput = btnPosition;
        btnPosition++;
        messageData[0] = refMessage;
        Serial.println(messageData[0].buttons);
      }
      else
      {
        break;
      }
      
    }
  }

}
