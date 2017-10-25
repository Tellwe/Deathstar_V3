#include "definitions.h"
#include "longRangeTransceiver.h"

#define signalOut RB6
#define signalIn RB7


static int answerReceived = 0;
static int stateChange =0;
static int state;
static int firstStateChange=0;
static int waitingForAnswer=0;
static int amountOfOutSignals=0;
static unsigned int *localMillisecondCounterPtr;
static int timeToNextOutSignal=500;
static int sendNewSignal =1;
static int timeToNextBlinkSignal=900;
static unsigned int begin1=0;
static unsigned int begin2=0;

// Registers the initial state
void longTranceiverConfig(unsigned int *millisecondCounterPtr)
{
	state=signalIn;
	localMillisecondCounterPtr = millisecondCounterPtr;
}

void updateLongRangeTranceiver(){
	//New State
	
	if(state != signalIn ){
		begin1 = *localMillisecondCounterPtr;
		state=signalIn;
		// There is for some unknown reason always a state change in the beginning
		if(firstStateChange==0)
			firstStateChange=1;
		else
			stateChange=1;
		// Only bounce back signal if waiting for answer
		if(waitingForAnswer ==1){
			answerReceived==1;
			waitingForAnswer=0;
		}else
			amountOfOutSignals=amountOfOutSignals+1;
	}
	
	// Send out signals
	unsigned int var = *localMillisecondCounterPtr - begin1;
	if(amountOfOutSignals>0 && var>timeToNextOutSignal ){
		signalOut=!signalOut;
		begin1 = *localMillisecondCounterPtr;
		amountOfOutSignals=amountOfOutSignals-1;
	}
			
}

// returns 1 if state has changed or answer has been received
int isBlinkSignalReceived(){
	int returnValue=0;
	if(stateChange==1){
		stateChange=0;
		returnValue= 1;
	}else if(answerReceived==1){
		answerReceived=0;
		returnValue= 1;
	}
	return returnValue;
}

void sendStartBlink(){

	
	unsigned int var2 = *localMillisecondCounterPtr - begin2;
	if (var2>timeToNextBlinkSignal)
	{
		amountOfOutSignals=amountOfOutSignals+1;
		waitingForAnswer =1;
		begin2 = *localMillisecondCounterPtr;
	}
	
		//amountOfOutSignals=amountOfOutSignals+1;
		//waitingForAnswer =1;
}

