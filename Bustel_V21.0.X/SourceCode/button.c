#include "definitions.h"
#include "time.h"
#include "button.h"

static int externalButtonState = 0;
int debounceCounter = 0;
static int numberOfSuccessfullDetections = 5	;
static int debouncePeriodMilliSeconds = 10;

void externalButtonConfig()
{

}
int externalButtonUpdate()
{
	static unsigned long begin;
	//If the active-state of the button has been detected, initiate debounce sequence
	if(externalButtonSignal == 1)
	{
		if((debounceCounter == 0) || ((clock() - begin) / CLOCKS_PER_MS > debouncePeriodMilliSeconds))
		{
			begin = clock();
			debounceCounter++;
		}
		else if(debounceCounter >= numberOfSuccessfullDetections)
		{
			externalButtonState = 1;
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
