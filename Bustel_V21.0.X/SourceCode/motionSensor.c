#include "definitions.h"
#include "motionSensor.h"

static int motionSensorState = 0;
static int debounceCounter = 0;
static int numberOfSuccessfullDetections = 50;
static int debouncePeriodMilliSeconds = 10;
static unsigned int *localMillisecondCounterPtr;

//Motion Sensor input
#define motionSensorSignal			RA1

void motionSensorConfig(unsigned int *millisecondCounterPtr)
{
	localMillisecondCounterPtr = millisecondCounterPtr;
	
}
int motionSensorUpdate()
{
	static unsigned int begin;
	//If the active-state of the motion sensor has been detected, initiate debounce sequence
	if(motionSensorSignal == 1)
	{
		unsigned int var = *localMillisecondCounterPtr - begin;
		if(debounceCounter == 0) 
		{
			begin = *localMillisecondCounterPtr;
			debounceCounter++;
		}
		else if(debounceCounter >= numberOfSuccessfullDetections)
		{
			motionSensorState = 1;
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
		motionSensorState = 0;
	}

	return 0;
}
int isMotionDetected()
{
	return motionSensorState;
}
