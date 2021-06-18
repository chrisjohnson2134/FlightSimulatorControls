#ifndef message_H
#define message_H

struct dataMessage {
	unsigned char status;
	unsigned short numButtons;
	unsigned int buttons;
	short xAxis;
	short yAxis;
	short zAxis;
	unsigned char hatDirection;
};

struct updateMessage {
	unsigned char status;
};

#endif
