#include "definitions.h"
#include "longRangeTransceiver.h"

#define signalOut RB6
#define signalIn RB7


static int answerReceived = 0;
static int stateChange =0;
static int state;
static int firstStateChange=0;
static int waitingForAnswer=0;

// Registers the initial state
void longTranceiverConfig()
{
	state=signalIn;
}

void updateLongRangeTranceiver(){


	//New State
	if(state != signalIn ){
		state=signalIn;
		// There is for some unknown reason always a state change in the beginning
		if(firstStateChange==0)
			firstStateChange=1;
		else
			stateChange=1;
		// Only bounce back signal if waiting for answer
		if(waitingForAnswer ==1){
			answerReceived==1;
		}else
			signalOut=!signalOut;
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
	signalOut=!signalOut;
	waitingForAnswer =1;

}
