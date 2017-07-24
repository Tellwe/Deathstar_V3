//Includes
#include <xc.h>
#include <time.h>
#include <stdio.h>

//Drivers
/*#include "button.h"
#include "ledBlink.h"
#include "ledLight.h"
#include "duskGuard.h"
#include "motionSensor.h"
*/
//Configuration
#include "configHW.h"

//Abbreviations
#include "definitions.h"

//Global variables
#include "globals.h"


/**********************		Description		*************************************** 					
***********************************************************************************/
//Configline for initial configuration of registers in the PIC processors
#pragma config DEBUG=OFF, LVP=OFF, FCMEN=OFF, IESO=OFF, BOREN=OFF, CPD=ON, CP=ON, MCLRE=OFF, PWRTE=OFF, WDTE=OFF, FOSC=INTRC_NOCLKOUT 

//*************************************************************************************


struct MyClocks{
	int halfSecond;
	int second;
	int minute;
};

struct MyClocks internalClock;




void main(){

	//Initiate clock
	internalClock.halfSecond = 0;
	internalClock.second = 0;
	internalClock.minute = 0;

	initialConfigurationP16F887();





	while(1){


	}

}

/*********************************************************************
 * void interrupt tc_int(void)
 *
 * Overview:        
 *              This function controlls the interrupt routine generated in the controller
 *				The interupt occurs every half-second
 * PreCondition:    
 *              Processor HW configured correctly
 *
 * Input:       
 *             
 * Output:      None
 *
 * Side Effects:    
 *              Update of counting registers
 *
 ********************************************************************/

void interrupt tc_int(void){
	//Check if interrupt on timer overflow
	if(TMR1IF == 1){
		//Stop timer
		TMR1ON = 0;
		//Populate the timer registers again with the correct value to achive 0,5s until a new overflow
		TMR1H = 0x0B;
		TMR1L = 0xDB;
		
		//Tick
		//unsigned long begin = clock();

		//Count  of the counter counting seconds for the application
		internalClock.halfSecond++;
		if(internalClock.halfSecond>=2)
		{
			internalClock.halfSecond = 0;
			internalClock.second++;
		}
		if(internalClock.second >=60)
		{
			internalClock.second = 0;
			internalClock.minute++;
		}
		if(internalClock.minute >= 60)
		{
			internalClock.minute = 0;
		}

		//Start Timer again
		TMR1ON = 1;

		//tock
//		unsigned long end = clock();
//		double time_spent = (double) (end-begin) / CLOCKS_PER_SEC;
 
	}
	TMR1IF = 0;			//Re-enable timer1-interrupt
	RBIF = 0;			//Re-enable interrupt-on-change for PORTB
    GIE = 1;			//Re-enable interrupts
return;
}
