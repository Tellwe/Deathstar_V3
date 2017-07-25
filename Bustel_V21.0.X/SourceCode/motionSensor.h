#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include "definitions.h"


//Functions for the driver
void motionSensorConfig(unsigned int *secondCounterPtr);
int motionSensorUpdate();
int isMotionDetected();

#endif