#ifndef LEDBLINK_H
#define LEDBLINK_H


#include "definitions.h"
//Header for the blink LED


//Configuration variables for the driver
//Enum with members for configuration for the blink  length
typedef enum 
{ 
	BLINK_LENGTH_OFF = 0,
	BLINK_MINUTES3, 
	BLINK_MINUTES5, 
	BLINK_MINUTES10, 
} blinkLength_type;



//Functions for the driver
void ledBlinkConfig(int *halfSecondCounterPtr, unsigned int *secondCounterPtr, blinkLength_type blinkLength);
int ledBlinkStart();
int ledBlinkUpdate();
int ledBlinkStop();

#endif