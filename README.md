# FlightSimulatorControls
This Project is designed to make an easily expandable cockpit for flight sims

This Project is for people that want to make their own cockpits and simplify the wiring
for a more module based system that allows them to change layouts much more quickly. 
I'd compare this ability to being  able to swap the instrument panel of a Cessana for a 
Boeing 747. 

# Architecture Overview

This is based around a hub and spokes model where the Master is the device that is directly interfacing with 
the windows HID driver. All other devices are polled by the master and the data is then transmitted to Windows.
~~Buttons inputs are dynamic, each slave knows how many buttons it has and has an unsigned integer that holds the state 
of each of the buttons. When the master polls the slave it will assign the joystick button to the corresponding slave 
input button.~~

# Goals : 
* Allow the user to easily connect a new module to the system.
* The Protocol to make a module should be easy to follow for the users.
* The System Should be able to handle binary and Analog Inputs.
* The System Should be able to adapt to new devices with a simple reset.

# More Goals : 
* Be able to send out Feedback from the master node to the slaves about pitch/yaw/roll, etc.
* Create standard Modules that the user can easily wire up and use. 
* Have Unique way to get user inputs from the modules. 
