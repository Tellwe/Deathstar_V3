#include "definitions.h"
#include "longRangeTransceiver.h"

#define signalOut RB6
#define signalIn RB7


static int varBlinkReqReceived = 0;
static int answerReceived = 0;
static int stateChange =0;
static int state;
static int signalReceived=0;
static int sendSignal=0;
static int waitingForAnswer=0;
static int debounceCounter = 0;
static int numberOfSuccessfullDetections = 5;
static int debouncePeriodMilliSeconds = 10;
static unsigned int *localMillisecondCounterPtr;

void longTranceiverConfig()
{
	//localMillisecondCounterPtr = millisecondCounterPtr;
	state=signalIn;
}

void updateLongRangeTranceiver(){


	//New State
	if(state != signalIn){
		state=signalIn;
		if(waitingForAnswer == 1){
			answerHasBeenReceived();	
		}
		blinkReqReceived();
	}
	//Not new state
	else{
		stateChange=0;
	}			
}
void blinkReqReceived(){
	varBlinkReqReceived = 1;
	sendStateChange(); //Send answer back

}
int isBlinkReqReceived(){
	if(varBlinkReqReceived){
		varBlinkReqReceived = 0;
		return 1;
	}
	else
		return 0;
}
void answerHasBeenReceived(){
	waitingForAnswer = 0;
	answerReceived = 1;
}
int hasAswerBeenReceived(){
	if(answerReceived == 1){
		answerReceived = 0;
		return 1;
	}
	else{
		return 0;
	}
		 
}
void sendStartBlink(){	
	sendStateChange();
	waitingForAnswer = 1;
}

void sendStateChange(){
	if(signalOut)
		signalOut = 0;
	else
		signalOut = 1;
}
