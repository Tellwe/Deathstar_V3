//Includes
#include <xc.h>
#include <time.h>
#include <stdio.h>

//Configuration
#include "config.h"
#include "configHW.h"

//Abbreviations
#include "definitions.h"

//Global variables
#include "globals.h"
//Drivers
#include "button.h"
#include "ledBlink.h"
#include "ledLight.h"
#include "duskGuard.h"
#include "motionSensor.h"

//Configline for initial configuration of registers in the PIC processors
#pragma config DEBUG=OFF, LVP=OFF, FCMEN=OFF, IESO=OFF, BOREN=OFF, CPD=ON, CP=ON, MCLRE=OFF, PWRTE=OFF, WDTE=OFF, FOSC=INTRC_NOCLKOUT 

void main(){
	//Customer
	struct Customer_struct customer = xtrafik;

	//Initiate clock
	internalClock.halfSecond = 0;
	internalClock.second = 0;
	internalClock.minute = 0;

	initialConfigurationP16F887();

	ledLightConfig(&secondsCounter, (lightLength_type) customer.ledsConfig.lightLength);
	ledBlinkConfig(&internalClock.halfSecond, &secondsCounter, (blinkLength_type) customer.ledsConfig.blinkLength);
	buttonConfig(&millisecondCounter);
	motionSensorConfig(&millisecondCounter);
	duskGuardConfig(&millisecondCounter, &secondsCounter, 30);

	while(1)
	{
		ledLightUpdate();
		ledBlinkUpdate();
		buttonUpdate();
		motionSensorUpdate();
		duskGuardUpdate();

		switch (customer.ledsConfig.lightTrigger){
			case LIGHT_OFF:
				break;
			case LIGHT_MOTION_SENSOR:
				if(isMotionDetected() == 1 && isItDusk() == 1)
				{
					ledLightStart();
				}
				break;
			case LIGHT_BUTTON:
				if(isButtonPushed() == 1 && isItDusk() == 1)
				{
					ledLightStart();
				}
				break;
			default:
				break;
		}

		switch (customer.ledsConfig.blinkTrigger){
			case BLINK_OFF:
				break;
			case BLINK_MOTION_SENSOR:
				if(isMotionDetected() == 1)
				{
					ledBlinkStart();
				}
				break;
			case BLINK_BUTTON:
				if(isButtonPushed() == 1)
				{
					ledBlinkStart();
				}
				break;
			default:
				break;
		}
	}
}

void interrupt tc_int(void){
	//Check if interrupt on timer overflow
	if(TMR1IF == 1){
		//Stop timer
		TMR1ON = 0;
		
		//Populate the timer registers again with the correct value to achive 0,1s until a new overflow
		TMR1H = 0xFB;
		TMR1L = 0x1D;
		
		//Tick
		//unsigned long begin = clock();

		//Count  of the counter counting seconds for the application
		millisecondCounter+=10;
		if(millisecondCounter == 500)
		{
			internalClock.halfSecond++;
			millisecondCounter = 0;
		}
		if(internalClock.halfSecond>=2)
		{
			internalClock.halfSecond = 0;
			internalClock.second++;
			secondsCounter++;
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
	GIE = 1;			//Re-enable interrupts
return;
}
