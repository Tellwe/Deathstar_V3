#ifndef LONGRANGETRANCEIVER_H
#define LONGRANGETRANCEIVER_H

#include "definitions.h"

typedef enum 
{ 
	TRANSMITTER,
	RECEIVER
} transceiver_type;


//Functions for the driver
void sendStartBlink();
void updateLongRangeTranceiver();
void longTranceiverConfig(unsigned int *millisecondCounterPtr,unsigned int *secondCounterPtr, transceiver_type type);
int isBlinkSignalReceived();





#endif