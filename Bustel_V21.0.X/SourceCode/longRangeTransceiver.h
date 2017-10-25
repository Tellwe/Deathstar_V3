#ifndef LONGRANGETRANCEIVER_H
#define LONGRANGETRANCEIVER_H

#include "definitions.h"


//Functions for the driver
void sendStartBlink();
void updateLongRangeTranceiver();
void longTranceiverConfig(unsigned int *millisecondCounterPtr);
int isBlinkSignalReceived();





#endif