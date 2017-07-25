#include "definitions.h"
#include "ledBlink.h"

//Driver for the Blink LED

unsigned int ledOnTimeInMinutes = 0;
unsigned int start_ts = 0;
unsigned int *localSecondCounterPtr;
int *localHalfSecondCounterPtr;
int ledBlinkOn = 0; //State variable


void ledBlinkConfig(int *halfSecondCounterPtr, unsigned int *secondCounterPtr, blinkCycleLength_type blinkCycleLength)
{
	localHalfSecondCounterPtr = halfSecondCounterPtr;
	localSecondCounterPtr = secondCounterPtr;
	blinkCycleLength_type localBlinkCycleLength = blinkCycleLength;
	
	switch (localBlinkCycleLength) {
		case BLINK_OFF:
			ledOnTimeInMinutes = 0;
			break;
		case BLINK_MINUTES3:
			ledOnTimeInMinutes = 3;
			break;
		case BLINK_MINUTES5:
			ledOnTimeInMinutes = 5;
			break;
		case BLINK_MINUTES10:
			ledOnTimeInMinutes = 10;
			break;
		default:
			ledOnTimeInMinutes = 0;
			break;
	}
	//return 0;
}

unsigned int stop_ts;
int ledBlinkStart()
{
	//Set the start timestamp
	if(ledBlinkOn == 0)
	{
		start_ts = *localSecondCounterPtr;
		ledBlinkOn = 1; //Turn on the LED
		return 0;
	}
	else
	{
		return 1;
	}
}
int ledBlinkUpdate()
{

	if(*localSecondCounterPtr == (start_ts + ledOnTimeInMinutes * 60))
		ledBlinkStop();

	if(ledBlinkOn == 1 && *localHalfSecondCounterPtr == 1)
		ledBlinkSignal = 1;
	else 
		ledBlinkSignal = 0;


	return 0;
}
int ledBlinkStop()
{
	ledBlinkOn = 0;
	return 0;
}