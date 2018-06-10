#ifndef CUSTOMERCONFIGURATIONS_H
#define CUSTOMERCONFIGURATIONS_H

#include "ledBlink.h"
#include "ledLight.h"

//Functions
void initiateCustomers();

//Configuration layer
typedef enum 
{ 
	LIGHT_OFF = 0,
	LIGHT_MOTION_SENSOR,
	LIGHT_BUTTON 
} lightTrigger_type;

typedef enum 
{ 
	BLINK_OFF = 0,
	BLINK_MOTION_SENSOR,
	BLINK_BUTTON
} blinkTrigger_type;

//Application layer
struct LedsConfig_struct{
	lightTrigger_type lightTrigger;
	lightLength_type lightLength;
	blinkTrigger_type blinkTrigger;
	blinkLength_type blinkLength;
};

//Customer
struct Customer_struct{
	struct LedsConfig_struct ledsConfig;
};

//Array for all customers
struct Customer_struct customers[16];


//Customer definitions
struct Customer_struct debugCustomer = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES3,
		BLINK_BUTTON,
		BLINK_MINUTES3
	}
};
struct Customer_struct xtrafik = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES5,
		BLINK_BUTTON,
		BLINK_MINUTES5
	}
};
struct Customer_struct xtrafik_pir = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES5,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES5
	}
};
struct Customer_struct varmlandsTrafikShelter = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES2,
		BLINK_BUTTON,
		BLINK_MINUTES10
	}
};
struct Customer_struct varmlandsTrafikPost = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_BUTTON,
		BLINK_MINUTES10
	}
};

#endif