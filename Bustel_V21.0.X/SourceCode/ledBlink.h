#ifndef LEDBLINK_H
#define LEDBLINK_H


#include "definitions.h"
//Header for the blink LED


//Configuration variables for the driver
//Enum with members for configuration for the blink cycle length
typedef enum 
{ 
	BLINK_OFF = 0,
	BLINK_MINUTES3, 
	BLINK_MINUTES5, 
	BLINK_MINUTES10, 
} blinkCycleLength_type;



//Functions for the driver
//void ledLightConfig(struct MyClocks *clockPtr, lightLength_type lightLength);
void ledBlinkConfig(unsigned int *secondCounterPtr, blinkCycleLength_type blinkCycleLength);
int ledBlinkStart();
int ledBlinkUpdate();
int ledBlinkStop();

#endif