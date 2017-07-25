#include <xc.h>
#include "definitions.h"
#include "duskGuard.h"

//Control for enabling analog measurement on HW
#define analogReadDisabledSignal	RC0

static unsigned int *localSecondCounterPtr;
static unsigned int *localmillisecondCounterPtr;
static int duskGuardState = 0;
static unsigned int localDuskCheckInterval = 0;
static unsigned int duskCheckTimeStamp = 0;
static unsigned int duskThresholdValue = 130;

int adStartedFlag = 0;
int adBusyFlag = 0;
unsigned int waitTimeStamp = 0;


void duskGuardConfig(unsigned int *millisecondCounterPtr, unsigned int *secondCounterPtr, unsigned int duskCheckInterval)
{
	localmillisecondCounterPtr = millisecondCounterPtr;
	localSecondCounterPtr = secondCounterPtr;
	localDuskCheckInterval = duskCheckInterval;
}
int duskGuardUpdate()
{
	if(*localSecondCounterPtr == duskCheckTimeStamp + localDuskCheckInterval)
	{
		startAnalogChannelRead(0);

	}
	if(adStartedFlag == 1)
	{
		int duskValue = updateAnalogChannelRead();
		if(duskValue > -1)
		{
			adStartedFlag = 0;
			duskGuardState = duskValue > duskThresholdValue;
		}

	}
	return 0;
}
int duskGuardGetState()
{
	return duskGuardState;
}

int startAnalogChannelRead(unsigned char channel)
{
	
	waitTimeStamp = *localmillisecondCounterPtr;

	analogReadDisabledSignal = 0;
	
	ADCON0bits.CHS = channel;
	ADCON0bits.ADON = 1;
	adStartedFlag = 1;


}
int updateAnalogChannelRead()
{
	if(*localmillisecondCounterPtr < waitTimeStamp + 100) //Delay for the analog reading to staibilize
	{
		ADCON0bits.GO = 1;
		adBusyFlag = 1;
	}
	if (adBusyFlag == 1) 
		if (ADCON0bits.GO)
		{
			ADCON0bits.ADON = 0;
			analogReadDisabledSignal = 1;
			adBusyFlag = 0;
			return ADRESH;
		}
	
	return -1;	
}
