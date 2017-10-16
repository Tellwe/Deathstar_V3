#include "definitions.h"
#include "longRangeTransceiver.h"

#define signalOut RB7
#define signalIn RB6


void sendTransState(int var){
	signalOut = var;
}


int transState(){
	return signalIn;
}
