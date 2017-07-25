#ifndef LEDLIGHT_H
#define LEDLIGHT_H


#include "definitions.h"
//Header for the light LED


//Configuration variables for the driver
//Enum with members for configuration for the light cycle length
typedef enum 
{ 
	LIGHT_LENGTH_OFF = 0,
	LIGHT_MINUTES2, 
	LIGHT_MINUTES3, 
	LIGHT_MINUTES5, 
	LIGHT_MINUTES10
} lightLength_type;



//Functions for the driver
void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength);
int ledLightStart();
int ledLightUpdate();
int ledLightStop();

#endif