#ifndef GLOBALS_H
#define GLOBALS_H

//Global variables for the project
struct MyClocks{
	int halfSecond;
	int second;
	int minute;
};

struct MyClocks internalClock;

unsigned int halfSecondCounter = 0;
unsigned int secondsCounter = 0;
unsigned int millisecondCounter = 0;



#endif