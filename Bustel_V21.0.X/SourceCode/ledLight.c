#include "definitions.h"
#include "ledLight.h"

//Driver for the Light LED

unsigned int ledOnTimeMinutes = 0;
unsigned int start_ts = 0;
unsigned int *localSecondCounterPtr;
int ledLightOn = 0;


//void ledLightConfig(struct MyClocks *clockPtr, lightLength_type lightLength)
void ledLightConfig(unsigned int *secondCounterPtr, lightLength_type lightLength)
{
	localSecondCounterPtr = secondCounterPtr;
	lightLength_type localLightLength = lightLength;
	
	switch (localLightLength) {
		case OFF:
			ledOnTimeMinutes = 0;
			break;
		case MINUTES2:
			ledOnTimeMinutes = 2;
			break;
		case MINUTES3:
			ledOnTimeMinutes = 3;
			break;
		case MINUTES5:
			ledOnTimeMinutes = 5;
			break;
		case MINUTES10:
			ledOnTimeMinutes = 10;
			break;
		default:
			ledOnTimeMinutes = 0;
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
int ledUpdate()
{

	if(*localSecondCounterPtr == (start_ts + ledOnTimeMinutes * 60))
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