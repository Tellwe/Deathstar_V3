//Includes
//Processor and compiler dependant
#include <xc.h>

//Drivers
#include "button.h"
#include "ledBlink.h"
#include "ledLight.h"
#include "duskGuard.h"
#include "motionSensor.h"

//Configuration
#include "config.h"

//Abbreviations
#include "definitions.h"


/**********************		Description		*************************************** 					
***********************************************************************************/
//Configline for initial configuration of registers in the PIC processors
#pragma config DEBUG=OFF, LVP=OFF, FCMEN=OFF, IESO=OFF, BOREN=OFF, CPD=ON, CP=ON, MCLRE=OFF, PWRTE=OFF, WDTE=OFF, FOSC=INTRC_NOCLKOUT 

//*************************************************************************************


void main(){
	

}


