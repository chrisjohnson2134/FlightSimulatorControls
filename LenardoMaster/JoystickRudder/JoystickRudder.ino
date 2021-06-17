#include <Joystick.h>

// Program used to test the USB Joystick object on the 
// Arduino Leonardo or Arduino Micro.

#include <Joystick.h>
#include <Wire.h>
#include "Message.h"

//dynamic struct
struct dynamicButtons {
  short address;
  short btnInput;
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

  while(!Serial);
  setupButtonMap();
  
  }


void loop() {

  int capture = 0;

//    Joystick.setButton(2,messageData.buttons & (1));
//    Joystick.setButton(3,messageData.buttons & (1 << 1));
//  Serial.println(messageData[1].buttons);
  delay(2000);
  Joystick.sendState();
    
}

//Get all the Values from each of the controllers.
void PollDevices()
{
  int i = 0;
  for(i =  1; i < 10; i++)//create timeout to get up to X devices
  {
    Wire.requestFrom(i, sizeof refMessage);
      while (Wire.available()) { // slave may send less than requested
        Wire.readBytes((byte *) &refMessage,sizeof refMessage); // receive a byte as character
     }
    messageData[i] = refMessage;
  }
}

//loop through dataMessages and set Joystick Buttons based off messages.
void SetButtonsJoystick()
{
  
}

//in the intial state the controller buttons will have how many buttons that it has,
//expressed in binary form 0x11 = 2 buttons. It will map each button of the device,
//to a dynamic list that will store the address of the device and the button input.
void setupButtonMap(){
  int i = 1,j = 0,btnPosition = 0;
  
  PollDevices();
  
  for(i =  1; i < 10; i++)//create timeout to get up to X devices
  {
    Serial.print("addr : ");
    Serial.println(i);
    
    for(j = j; j < 32; j++)
    {
      if(messageData[i].buttons & (1 << j))
      {
        buttonLocationArr[j].address = i;
        buttonLocationArr[j].btnInput = btnPosition;
        btnPosition++;
        Serial.println(messageData[i].buttons);
        messageData[i].buttons = 0;
      }
      else
      {
        break;
      }
      
    }
  }

}
