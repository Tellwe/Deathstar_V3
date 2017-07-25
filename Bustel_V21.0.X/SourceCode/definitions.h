#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <xc.h>

//File containing all the abbreviations used in the project

//Variables for the project
#define CLOCKS_PER_MS	4000





//Map towards HW registers from xc.h
//LED Light output
#define ledLightSignal				RC2
//LED Blink output
#define ledBlinkSignal				RC1
//External button input
#define externalButtonSignal		RB5
//Onboard button input
#define onboardButtonSignal			RB0
//Motion Sensor input
#define motionSensorSignal			RA1
//Control for enabling analog measurement on HW
#define disableAnalogReadingSignal	RC0


#endif