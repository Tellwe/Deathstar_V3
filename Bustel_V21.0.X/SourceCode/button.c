#include "definitions.h"
#include "button.h"

static int externalButtonState = 0;
int debounceCounter = 0;
static int numberOfSuccessfullDetections = 5;
static int debouncePeriodMilliSeconds = 10;
unsigned int *localMillisecondCounterPtr;


void externalButtonConfig(unsigned int *millisecondCounterPtr)
{
	localMillisecondCounterPtr = millisecondCounterPtr;
	
}
int externalButtonUpdate()
{
	static unsigned int begin;
	//If the active-state of the button has been detected, initiate debounce sequence
	if(externalButtonSignal == 0)
	{
		unsigned int var = *localMillisecondCounterPtr - begin;
		if(debounceCounter == 0) 
		{
			begin = *localMillisecondCounterPtr;
			debounceCounter++;
		}
		else if(debounceCounter >= numberOfSuccessfullDetections)
		{
			externalButtonState = 1;
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
		externalButtonState = 0;
	}

	return 0;
}
int externalButtonGetState()
{
	return externalButtonState;
}
