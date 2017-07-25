#ifndef BUTTON_H
#define BUTTON_H

#include "definitions.h"


//Functions for the driver
void buttonConfig(unsigned int *secondCounterPtr);
int buttonUpdate();
int buttonGetState();

#endif