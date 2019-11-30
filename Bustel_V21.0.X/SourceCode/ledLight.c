#include "definitions.h"
#include "ledLight.h"

//Driver for the Light LED

static unsigned int ledOnTimeInMinutes = 0;
static unsigned int lightStartTimeStamp = 0;
static unsigned int *localSecondCounterPtr;
static int ledLightOnFlag = 0; //State variable

//LED Light output
#define ledLightSignal				RD6

void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength)
{
	localSecondCounterPtr = secondCounterPtr;
//Special fix for long range unit. Light function is off allways.

//	lightLength_type localLightLength = lightLength;
	lightLength_type localLightLength = LIGHT_LENGTH_OFF;
	
	switch (localLightLength) {
		case LIGHT_LENGTH_OFF:
			ledOnTimeInMinutes = 0;
			break;
		case LIGHT_MINUTES2:
			ledOnTimeInMinutes = 2;
			break;
		case LIGHT_MINUTES3:
			ledOnTimeInMinutes = 3;
			break;
		case LIGHT_MINUTES5:
			ledOnTimeInMinutes = 5;
			break;
		case LIGHT_MINUTES10:
			ledOnTimeInMinutes = 10;
			break;
		default:
			ledOnTimeInMinutes = 0;
			break;
	}
	//return 0;
}

unsigned int stop_ts;
int ledLightStart()
{
	//Set the start timestamp
	if(ledLightOnFlag == 0)
	{
		lightStartTimeStamp = *localSecondCounterPtr;
		ledLightOnFlag = 1; //Turn on the LED
		return 0;
	}
	else
	{
		return 1;
	}
}
int ledLightUpdate()
{

	if(*localSecondCounterPtr == (lightStartTimeStamp + ledOnTimeInMinutes * 60))
		ledLightStop();

	if(ledLightOnFlag == 1)
		ledLightSignal = 1;
	else 
		ledLightSignal = 0;


	return 0;
}
int ledLightStop()
{
	ledLightOnFlag = 0;
	return 0;
}