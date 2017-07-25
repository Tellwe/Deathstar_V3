#ifndef DUSKGUARD_H
#define DUSKGUARD_H

#include "definitions.h"

//Functions for the driver
void duskGuardConfig(unsigned int *millisecondCounterPtr, unsigned int *secondCounterPtr, unsigned int duskCheckInterval);
int duskGuardUpdate();
int duskGuardGetState();
void startAnalogChannelRead(unsigned char channel);
int updateAnalogChannelRead();

#endif
