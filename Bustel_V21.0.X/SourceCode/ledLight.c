#include "ledLight.h"
//Driver for the Light LED

struct MyClocks *localClockPtr;
int ledLength = 0;

//void ledLightConfig(struct MyClocks *clockPtr, lightLength_type lightLength)
void ledLightConfig(lightLength_type lightLength)
{
	//localClockPtr = clockPtr;
	lightLength_type localLightLength = lightLength;
	
	switch (localLightLength) {
		case OFF:
			ledLength = 0;
			break;
		case MINUTES2:
			ledLength = 2;
			break;
		case MINUTES3:
			ledLength = 3;
			break;
		case MINUTES5:
			ledLength = 5;
			break;
		case MINUTES10:
			ledLength = 10;
			break;
		default:
			ledLength = 0;
			break;
	}
	//return 0;
}

int ledLightStart(){
	


	return 0;
}

int ledLightOff(){
	return 0;
}