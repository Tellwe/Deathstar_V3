#include <xc.h>
#include "pianokeys.h"

#define pianoKeyInputPort	PORTD

int pianoKeyNumber(){
	return pianoKeyInputPort & 0b00011111; 
}