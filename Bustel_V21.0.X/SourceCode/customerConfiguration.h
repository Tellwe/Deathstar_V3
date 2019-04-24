#ifndef CUSTOMERCONFIGURATIONS_H
#define CUSTOMERCONFIGURATIONS_H

#include "ledBlink.h"
#include "ledLight.h"
#include "transceiver.h"

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
	BLINK_BUTTON,
	BLINK_RECEIVER,
	BLINK_TRANSMITTER_PIR,
	BLINK_TRANSMITTER_BUTTON
} blinkTrigger_type;
 
//Application layer
struct LedsConfig_struct{
	lightTrigger_type lightTrigger;
	lightLength_type lightLength;
	blinkTrigger_type blinkTrigger;
	blinkLength_type blinkLength;
	transceiverNode_type transceiverNode;
};

//Customer
struct Customer_struct{
	struct LedsConfig_struct ledsConfig;
};

//Array for all customers
    struct Customer_struct customers[16];


//Customer definitions

//Customer XTrafik
//Uncommment block in this file + customerConfiguration.c	
//*******************************************************************
/*
struct Customer_struct xtrafik = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES5,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES5,
		NODE1
	}
};
struct Customer_struct xtrafik_pir = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES5,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES5,
		NODE1
	}
};
struct Customer_struct wirelessReceiver5MinN1 = {
	{
		LIGHT_OFF,
		LIGHT_MINUTES5,
		BLINK_RECEIVER,
		BLINK_MINUTES5,
		NODE1
	}
};
struct Customer_struct wirelessReceiver5MinN2 = {
	{
		LIGHT_OFF,
		LIGHT_MINUTES5,
		BLINK_RECEIVER,
		BLINK_MINUTES5,
		NODE2
	}
};
struct Customer_struct wirelessTransmitterPIR5MinN1 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES5,
		BLINK_TRANSMITTER_PIR,
		BLINK_MINUTES5,
		NODE1
	}
};
struct Customer_struct wirelessTransmitterPIR5MinN2 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES5,
		BLINK_TRANSMITTER_PIR,
		BLINK_MINUTES5,
		NODE2
	}
};
struct Customer_struct wirelessTransmitterButton5MinN1 = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES5,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES5,
		NODE1
	}
};
struct Customer_struct wirelessTransmitterButton5MinN2 = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES5,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES5,
		NODE2
	}
};
//*******************************************************************
*/

//Customer Värmlandstrafik
//Uncommment block in this file + customerConfiguration.c	
//*******************************************************************

struct Customer_struct varmlandsTrafikShelter = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES2,
		BLINK_BUTTON,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct varmlandsTrafikPost = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_BUTTON,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct varmlandsTrafikPIR = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES10,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct wirelessReceiver10MinN1 = {
	{
		LIGHT_OFF,
		LIGHT_MINUTES10,
		BLINK_RECEIVER,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct wirelessReceiver10MinN2 = {
	{
		LIGHT_OFF,
		LIGHT_MINUTES10,
		BLINK_RECEIVER,
		BLINK_MINUTES10,
		NODE2
	}
};
struct Customer_struct wirelessTransmitterPIR10MinN1 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES10,
		BLINK_TRANSMITTER_PIR,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct wirelessTransmitterPIR10MinN2 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES10,
		BLINK_TRANSMITTER_PIR,
		BLINK_MINUTES10,
		NODE2
	}
};
struct Customer_struct wirelessTransmitterButton10MinN1 = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct wirelessTransmitterButton10MinN2 = {
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES10,
		NODE2
	}
};
struct Customer_struct wirelessTransmitterButton10MinPIR2MinN1 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES2,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES10,
		NODE1
	}
};
struct Customer_struct wirelessTransmitterButton10MinPIR2MinN2 = {
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES2,
		BLINK_TRANSMITTER_BUTTON,
		BLINK_MINUTES10,
		NODE2
	}
};
//*******************************************************************






#endif