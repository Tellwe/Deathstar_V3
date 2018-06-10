#include <xc.h>
#include "pianokeys.h"

#define pianoKeyInputPort	PORTD

int pianoKeyNumber(){
	return ~PORTD & 0b00011111; 
}