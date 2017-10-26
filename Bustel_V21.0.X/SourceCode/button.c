#include "definitions.h"
#include "button.h"

static int buttonState = 0;
static int debounceCounter = 0;
static int numberOfSuccessfullDetections = 5;
static int debouncePeriodMilliSeconds = 10;
static unsigned int *localMillisecondCounterPtr;


//Button input
#define buttonSignal		RB5


void buttonConfig(unsigned int *millisecondCounterPtr)
{
	localMillisecondCounterPtr = millisecondCounterPtr;
	
}
int buttonUpdate()
{
	static unsigned int begin;
	//If the active-state of the button has been detected, initiate debounce sequence
	if(buttonSignal == 0)
	{
		unsigned int var = *localMillisecondCounterPtr - begin;
		if(debounceCounter == 0) 
		{
			begin = *localMillisecondCounterPtr;
			debounceCounter++;
		}
		else if(debounceCounter >= numberOfSuccessfullDetections)
		{
			buttonState = 1;
		}
		else if(var >= debouncePeriodMilliSeconds)
		{
			begin = *localMillisecondCounterPtr;
			debounceCounter++;

		}
	}
	else
	{
		debounceCounter = 0;
		buttonState = 0;
	}

	return 0;
}
int isButtonPushed()
{
	return buttonState;
}
