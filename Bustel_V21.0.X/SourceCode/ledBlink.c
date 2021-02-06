#include "definitions.h"
#include "ledBlink.h"

//Driver for the Blink LED

static unsigned int ledOnTimeInMinutes = 0;
static unsigned int blinkStartTimeStamp = 0;
static unsigned int *localSecondCounterPtr;
static unsigned int *localMilliSecondCounterPtr;
static int ledBlinkOn = 0; //State variable

//LED Blink output
#define ledBlinkSignal				RD5 //LIGHT A
#define ledBlinkSignalSlave			RD7 //LIGHT C


void ledBlinkConfig(unsigned int *milliSecondCounterPtr, unsigned int *secondCounterPtr, blinkLength_type blinkLength)
{
	localMilliSecondCounterPtr = milliSecondCounterPtr;
	localSecondCounterPtr = secondCounterPtr;
	blinkLength_type localBlinkLength = blinkLength;
	
	switch (localBlinkLength) {
		case BLINK_LENGTH_OFF:
			ledOnTimeInMinutes = 0;
			break;
		case BLINK_MINUTES3:
			ledOnTimeInMinutes = 3;
			break;
		case BLINK_MINUTES5:
			ledOnTimeInMinutes = 5;
			break;
		case BLINK_MINUTES10:
			ledOnTimeInMinutes = 20;
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
		blinkStartTimeStamp = *localSecondCounterPtr;
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

	if(*localSecondCounterPtr == (blinkStartTimeStamp + ledOnTimeInMinutes * 60))
		ledBlinkStop();

	if(ledBlinkOn == 1){
		ledBlinkSignal = 1;
		ledBlinkSignalSlave = 1;
	}
	else {
		ledBlinkSignal = 0;
		ledBlinkSignalSlave = 0;
	}


	return 0;
}
int ledBlinkStop()
{
	ledBlinkOn = 0;
	return 0;
}