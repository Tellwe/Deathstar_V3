#include "definitions.h"
#include "ledLight.h"

//Driver for the Light LED

static unsigned int ledOnTimeInMinutes = 0;
unsigned int start_ts = 0;
unsigned int *localSecondCounterPtr;
int ledLightOnFlag = 0; //State variable

//LED Light output
#define ledLightSignal				RC2

void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength)
{
	localSecondCounterPtr = secondCounterPtr;
	lightLength_type localLightLength = lightLength;
	
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
		start_ts = *localSecondCounterPtr;
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

	if(*localSecondCounterPtr == (start_ts + ledOnTimeInMinutes * 60))
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