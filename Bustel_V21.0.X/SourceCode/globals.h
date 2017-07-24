

//Clock
int intHalfSecondCounter;			//Counts half seconds in interruptroutine
int intSecondCounter;				//Counts seconds in interruptroutine
int intMinuteCounter;				//Counts minutes in interruptroutine

struct Clock{
	int halfSecond;
	int second;
	int minute;
} internalClock;