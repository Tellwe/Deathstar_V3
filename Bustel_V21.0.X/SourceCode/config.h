#include "ledBlink.h"
#include "ledLight.h"

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
	BLINK_LONGRANGETRANCEIVER
} blinkTrigger_type;

typedef enum 
{ 
	TRANSCEIVER_OFF = 0,
	TRANCEIVER_BUTTON
} transceiverTrigger_type;

//Application layer
struct LedsConfig_struct{
	lightTrigger_type lightTrigger;
	lightLength_type lightLength;
	blinkTrigger_type blinkTrigger;
	blinkLength_type blinkLength;
	transceiverTrigger_type transceiverTrigger;
};

//Customer
struct Customer_struct{
	char name[30];	
	struct LedsConfig_struct ledsConfig;
};

//Customer definitions
struct Customer_struct debugCustomer = {
	"DEBUG",
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES3,
		BLINK_BUTTON,
		BLINK_MINUTES3
	}
};
/*struct Customer_struct xtrafik = {
	"XTrafik",
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES5,
		BLINK_BUTTON,
		BLINK_MINUTES5
	}
};*/
	/*
struct Customer_struct xtrafik_pir = {
	"XTrafik, PIR Trigger",
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES5,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES5
	}
};
struct Customer_struct varmlandsTrafikShelter = {
	"VarmlandsTrafik Kur",
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES2,
		BLINK_BUTTON,
		BLINK_MINUTES10
	}
};

struct Customer_struct varmlandsTrafikPost = {
	"VarmlandsTrafik Stolpe",
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_BUTTON,
		BLINK_MINUTES10
	}
};
*/
struct Customer_struct testLongRangeTranceiver = {
	"Test for long range tranceiver",
	{
		LIGHT_BUTTON,
		LIGHT_MINUTES10,
		BLINK_LONGRANGETRANCEIVER,
		BLINK_MINUTES10,
		TRANCEIVER_BUTTON
	}
};