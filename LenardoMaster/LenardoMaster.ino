#include <Joystick.h>

// For Possibly more flexibility
// https://github.com/MHeironimus/ArduinoJoystickLibrary/issues/100

#include <Joystick.h>
#include <Wire.h>
#include "Message.h"

// Create Joystick
Joystick_ Joystick;

//Constant
const int AVAILABLE_ADDRESSES = 10;

dataMessage messageData[10];
dataMessage refMessage;

void setup() {
  Serial.begin(9600);

  Joystick.begin();

  Wire.begin();

  while (!Serial);

}

void loop() {
  PollDevices();
  SetJoystick();

  Joystick.sendState();
}

//Get all the Values from each of the controllers.
void PollDevices()
{
  int i = 0;
  for (i =  1; i < AVAILABLE_ADDRESSES; i++) //create timeout to get up to X devices
  {
    Wire.requestFrom(i, sizeof refMessage);
    while (Wire.available()) { // slave may send less than requested
      Wire.readBytes((byte *) &refMessage, sizeof refMessage); // receive a byte as character
    }
    messageData[i] = refMessage;
  }
}

//loop through dataMessages and set Joystick Buttons based off messages.
void SetJoystick()
{
  int i = 0, j = 0, btnIndex = 0;

  for (i = 0; i < AVAILABLE_ADDRESSES; i++)
  {
    for (j = 0; j < messageData[i].numButtons; j++)
    {
      Joystick.setButton(btnIndex, messageData[i].buttons & (1 << j));
      btnIndex++;
    }
  }
}
