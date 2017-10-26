#include "definitions.h"
#include "longRangeTransceiver.h"

#define signalOut RB6
#define signalIn RB7

static int isReceiver=0;
static int isTransmitter =0;
static int answerReceived = 0;
static int stateChange =0;
static int state;
static int firstStateChange=0;
static int waitingForAnswer=0;
static int amountOfOutSignals=0;
static unsigned int *localMillisecondCounterPtr;
static unsigned int *localSecondCounterPtr;
static int timeToNextOutSignal=1;
static int timeToNextBlinkSignal=5;
static int timeToReceiveAnswer=4;
static unsigned int begin1=0;
static unsigned int begin2=0;
static unsigned int begin3=0;

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
		// There is for some unknown reason always a state change in the beginning
		state=signalIn;
		if(firstStateChange==0)
			firstStateChange=1;
		else if(firstStateChange==1 && isTransmitter==0){
			firstStateChange=2;
			isReceiver=1;
		}
		else{
			stateChange=1;
			begin1 = *localSecondCounterPtr;
			if(isReceiver==1){
				mountOfOutSignals=amountOfOutSignals+1;
			}
			if(isTransmitter==1){
				unsigned int var1 = *localSecondCounterPtr - begin2;
				if(var1<timeToReceiveAnswer)
					answerReceived==1;
			}
			/*		
			// Only bounce back signal if waiting for answer
			unsigned int var1 = *localSecondCounterPtr - begin2;
			if(var1<timeToReceiveAnswer)
				answerReceived==1;
			else
				amountOfOutSignals=amountOfOutSignals+1;
				*/
		}
	}
	// Send out signals. There is a time delay here to give the transceiver time to reload
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
	isTransmitter=1;
	// Adds a signal to be sent out when tranceiver is ready.
	unsigned int var2 = *localSecondCounterPtr - begin2;
	if (var2>timeToNextBlinkSignal)
	{
		amountOfOutSignals=amountOfOutSignals+1;
		begin2 = *localSecondCounterPtr;
	}
}

