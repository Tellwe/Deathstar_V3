#include <xc.h>
#include "definitions.h"
#include "duskGuard.h"

static unsigned int *localSecondCounterPtr;
static unsigned int *localmillisecondCounterPtr;
static int duskGuardState = 0;
static unsigned int localDuskCheckInterval = 0;
static unsigned int duskCheckTimeStamp = 0;
static unsigned int duskThresholdValue = 130;

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

	}
	return 0;
}
int duskGuardGetState()
{
	return duskGuardState;
}
void DarknessCheck(void)
{

	if(AnalogValue(0)>duskThresholdValue)
		duskGuardState = 1;
	else
		duskGuardState = 0;
		
}
unsigned char AnalogValue(unsigned char channel)
{
	unsigned int waitTimeStamp = 0;
	waitTimeStamp = *localmillisecondCounterPtr;

	disableAnalogReadingSignal = 0;
	
	ADCON0bits.CHS = channel;
	ADCON0bits.ADON = 1;

	while(*localmillisecondCounterPtr < waitTimeStamp + 100); //Delay for the analog reading to staibilize

	ADCON0bits.GO = 1;

	while(*localmillisecondCounterPtr < waitTimeStamp + 100); //Delay for the analog reading to staibilize

	while(ADCON0bits.GO);
	
	ADCON0bits.ADON = 0;
	
	disableAnalogReadingSignal = 1;
	
	return ADRESH;

}
