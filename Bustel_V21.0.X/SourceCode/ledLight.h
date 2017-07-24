#ifndef LEDLIGHT_H
#define LEDLIGHT_H


#include "definitions.h"
//Header for the light LED


//Configuration variables for the driver
typedef enum 
{ 
	OFF = 0,
	MINUTES2, 
	MINUTES3, 
	MINUTES5, 
	MINUTES10
} lightLength_type;



//Functions for the driver
//void ledLightConfig(struct MyClocks *clockPtr, lightLength_type lightLength);
void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength);
int ledLightStart();
int ledUpdate();
int ledLightStop();

#endif