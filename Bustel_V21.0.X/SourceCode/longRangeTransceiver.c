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
static unsigned int *localSecondCounterPtr;
static int timeToNextOutSignal=3;
static int timeToNextBlinkSignal=2;
static int timeToReceiveAnswer=6;
static unsigned int begin1=0;
static unsigned int begin2=0;

// Registers the initial state
void longTranceiverConfig(unsigned int *millisecondCounterPtr,unsigned int *secondCounterPtr)
{
	state=signalIn;
	localMillisecondCounterPtr = millisecondCounterPtr;
	localSecondCounterPtr = secondCounterPtr;
}

void updateLongRangeTranceiver(){
	//New State
	if(state != signalIn ){
		
		state=signalIn;
		// There is for some unknown reason always a state change in the beginning
		if(firstStateChange==0)
			firstStateChange=1;
		else{
			stateChange=1;
			begin1 = *localSecondCounterPtr;
		}
		// Only bounce back signal if waiting for answer
		unsigned int var1 = *localSecondCounterPtr - begin2;
		if(var1<timeToReceiveAnswer)
			answerReceived==1;
		else
			amountOfOutSignals=amountOfOutSignals+1;
		/*
		if(waitingForAnswer ==1){
			answerReceived==1;
			waitingForAnswer=0;
		}else
			amountOfOutSignals=amountOfOutSignals+1;
			*/
	}
	
	// Send out signals
	unsigned int var = *localSecondCounterPtr - begin1;
	if(amountOfOutSignals>0 && var>timeToNextOutSignal ){
		signalOut=!signalOut;
		begin1 = *localSecondCounterPtr;
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

	unsigned int var2 = *localSecondCounterPtr - begin2;
	if (var2>timeToNextBlinkSignal)
	{
		amountOfOutSignals=amountOfOutSignals+1;
		waitingForAnswer =1;
		begin2 = *localSecondCounterPtr;
	}
}

