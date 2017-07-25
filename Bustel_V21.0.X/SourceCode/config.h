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
	char name[20];	
	struct LedsConfig_struct ledsConfig;
};

//Customer definitions
struct Customer_struct xtrafik = {
	"XTrafik",
	{
		LIGHT_MOTION_SENSOR,
		LIGHT_MINUTES3,
		BLINK_MOTION_SENSOR,
		BLINK_MINUTES3
	}
};
