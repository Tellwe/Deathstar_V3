#include "definitions.h"
#include "ledLight.h"

//Driver for the Light LED

unsigned int ledOnTimeInMinutes = 0;
unsigned int start_ts = 0;
unsigned int *localSecondCounterPtr;
int ledLightOn = 0; //State variable


void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength)
{
	localSecondCounterPtr = secondCounterPtr;
	lightLength_type localLightLength = lightLength;
	
	switch (localLightLength) {
		case LIGHT_OFF:
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
	if(ledLightOn == 0)
	{
		start_ts = *localSecondCounterPtr;
		ledLightOn = 1; //Turn on the LED
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

	if(ledLightOn == 1)
		ledLightSignal = 1;
	else 
		ledLightSignal = 0;


	return 0;
}
int ledLightStop()
{
	ledLightOn = 0;
	return 0;
}