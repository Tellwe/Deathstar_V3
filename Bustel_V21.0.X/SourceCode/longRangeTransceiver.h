#ifndef LONGRANGETRANCEIVER_H
#define LONGRANGETRANCEIVER_H

#include "definitions.h"


//Functions for the driver
void sendStartBlink();
int transState();
void updateLongRangeTranceiver();
void longTranceiverConfig();

void sendStateChange();

void answerHasBeenReceived();
int hasAswerBeenReceived();

void blinkReqReceived();
int isBlinkReqReceived();





#endif