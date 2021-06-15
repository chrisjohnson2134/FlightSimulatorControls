#ifndef message_H
#define message_H

struct dataMessage {
	unsigned char status;
	unsigned int buttons;
	unsigned short xAxis;
	unsigned short yAxis;
	unsigned short zAxis;
	unsigned char hatDirection;
};

struct updateMessage {
	unsigned char status;
};

#endif
