#ifndef BUTTON_H
#define BUTTON_H

#include "definitions.h"


//Functions for the driver
void externalButtonConfig(unsigned int *secondCounterPtr);
int externalButtonUpdate();
int externalButtonGetState();

#endif