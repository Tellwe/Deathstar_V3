#include "transceiver.h"
#include <xc.h>
#include <string.h>
#include "GenericTypeDefs.h"

//Driver for the Transceiver 
//Variables for the transceiver
static int wirelessId = 0;
static int startTriggerReceivedState = 0;
static int messageReceivedState = 0;
static int RF_Mode = RF_STANDBY;
static int driverUpdateState = 0;
static int transceiverActive = 0;
static unsigned int *localMilliSecondCounterPtr;
static unsigned int delayTimestamp = 0;
static unsigned int timeoutTransmissionTS = 0;



void transceiverConfig(int id, int isTransceiverActive, unsigned int *milliSecondCounterPtr)
{
	localMilliSecondCounterPtr = milliSecondCounterPtr;

	transceiverConfigRegisterSet(GCONREG, 0x30);					//Set to the right frequency 
	transceiverConfigRegisterSet(DMODREG,(0xA8)); 				//Set transiver into buffer mode
	transceiverConfigRegisterSet(FDEVREG, 0x09);	//0x09			//Set the frequency deeviation to 40KHz
	transceiverConfigRegisterSet(BRSREG, 0x07);	//0x09			//Set the bitrate to 25kbps	
	transceiverConfigRegisterSet(FIFOCREG,(0x0A));				//Set the FIFO-size to 16 bytes and the treshhold for interrupts to 10
	transceiverConfigRegisterSet(FTXRXIREG,(0x00|0xB0|0x09));	//IRQ0RX = nFIFOEmpty, IRQ1RX = FIFO_THRESHOLD, IRQ0TX = nFIFOEMPTY, IRQ1TX = TXDONE
	transceiverConfigRegisterSet(FTPRIREG,(0x01|0x10|0x01));	//	//Start to till FIFO when sync word is detected, start transmission when FIFO_not_full
	transceiverConfigRegisterSet(FILCREG, 0xA3);					//FIltersetting for the transiver
	transceiverConfigRegisterSet(SYNCREG,(0x18|0x20|0x06));		//SYNC-word enabled, 32 bit size, 3 errors allowed
	transceiverConfigRegisterSet(SYNCV31REG,('S'));				//
	transceiverConfigRegisterSet(SYNCV23REG,('Y'));				//
	transceiverConfigRegisterSet(SYNCV15REG,('N'));				//
	transceiverConfigRegisterSet(SYNCV07REG,('C'));				//
	transceiverConfigRegisterSet(TXCONREG, 0x72);			 	//Transmitt parameters
	transceiverConfigRegisterSet(CLKOUTREG, 0x3C);				//Dissable CLKOUT
	transceiverConfigRegisterSet(FCRCREG, 0x80);
	transceiverConfigRegisterSet(GCONREG, (transceiverConfigRegisterRead(GCONREG)|0x01));
		
	if(FindChannel() == 1);
	
	SetRFMode(RF_SLEEP);

	wirelessId = id;
	transceiverActive = isTransceiverActive;
	if(transceiverActive)
		driverUpdateState = 1;
}
void transceiverUpdate()
{
	//Flow for receiver
	if(RF_Mode != RF_RECEIVER && transceiverActive){
		if(driverUpdateState == 1){
			SetRFMode(RF_STANDBY);
			driverUpdateState = 2;
			delayTimestamp = *localMilliSecondCounterPtr;
		}
		if(driverUpdateState == 2){
			if(*localMilliSecondCounterPtr - delayTimestamp > 10){
				RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
				SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
				delayTimestamp = *localMilliSecondCounterPtr;
				driverUpdateState = 3;
			}
			else
				return;
		}	
		if(driverUpdateState == 3){
			if((RegisterRead(FTPRIREG) & 0b00000010) != 0)
			{
				driverUpdateState = 4;
			}
			else if(*localMilliSecondCounterPtr - delayTimestamp > 5000)
			{
				FindChannel();
				driverUpdateState = 4;
			}
			else 
			{
				return;
			}
		}
		if(driverUpdateState == 4){
			SetRFMode(RF_RECEIVER);
			driverUpdateState = 1;			
		}
	}




	//If message received on the receiver
	if(irq1Signal && RF_Mode == RF_RECEIVER){	
		unsigned char Data[30];//Char string containing the data received from the transiver
		delayTimestamp = *localMilliSecondCounterPtr;
		SetRFMode(RF_STANDBY);
		int i = 0;
		for (int j = 0; j < 30; ++j)
		{
			Data[j] = 0;
		}
		while(irqoSignal && *localMilliSecondCounterPtr - delayTimestamp < 4000)							//Read the FIFO from the transiver until the FIFO is empty 
		{
			Data[i] = ReadFIFO();				//Place bytes in the string for received data
			i++;
		}
		SetRFMode(RF_SLEEP);								//Set the transiver into sleep-mode	

		//Backward compatibility for the old transmitters
		//Check data to se what command that has been sent 
		if((strstr(Data, "N1BLINK")) && (wirelessId == 1))					//Requsted node == 1
		{
			messageReceivedState = 1;		
		}
		else if((strstr(Data, "N2BLINK")) && (wirelessId == 2))				//Requested node == 2
		{
			messageReceivedState = 1;
		}
		//End of backward compatibility

		if(Data[0] == STARTCHAR && Data[3] == ENDCHAR)
		{
			if(Data[1] == BUSSIGNAL)
			{
				if((Data[2] == NODE1 && wirelessId == 1) || (Data[2] == NODE2 && wirelessId == 2) || (Data[2] == NODE3 && wirelessId == 3))
					messageReceivedState = 1;
				if((Data[2] == NODE1STARTED && wirelessId == 1) || (Data[2] == NODE2STARTED && wirelessId == 2) || (Data[2] == NODE3STARTED && wirelessId == 3))
					startTriggerReceivedState = 1;
			} 
		}


	}
}
void TransmittPacket(unsigned char topic, unsigned char value)
{
	timeoutTransmissionTS = *localMilliSecondCounterPtr;
	int i = 0;
	int timeCalc = 0;

	__delay_ms(1000);

	//Initiation of transmitt sequence
	SetRFMode(RF_STANDBY);								//Transiver into Standby
	__delay_ms(10);										//Wait for oscillator to wake up
	RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
	SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
	while((RegisterRead(FTPRIREG) & 0b00000010) == 0)	//Wait for the PLL to lock
	{
		if(*localMilliSecondCounterPtr - timeoutTransmissionTS > 5000)
		{
			FindChannel();
			break;	
		}
		
	}
	SetRFMode(RF_TRANSMITTER);							//Set the transiver into tranmitt mode
	__delay_us(500);									//Transmitter wake-up time
	WriteFIFO('S');
	WriteFIFO('Y');
	WriteFIFO('N');
	WriteFIFO('C');

	//Transmitt data packet
	WriteFIFO(STARTCHAR);
	WriteFIFO(topic);
	WriteFIFO(value);
	WriteFIFO(ENDCHAR);
	//wait for transmitt done, set the transiver back to sleep
	while(!irq1Signal)
	{
		if(*localMilliSecondCounterPtr - timeoutTransmissionTS > 5000)
			break;
	}
	__delay_us(10);
	SetRFMode(RF_SLEEP);
	__delay_ms(50);
}
void transceiverConfigRegisterSet(unsigned char adress, unsigned char value)
{
    csconSignal = 0;
    adress = (adress<<1);
    writeByteToSPI(adress);
    writeByteToSPI(value);
    csconSignal = 1;
}
unsigned char transceiverConfigRegisterRead(unsigned char adress)
{
	unsigned char value;
    csconSignal = 0;
    adress = ((adress<<1)|0x40);
    writeByteToSPI(adress); 
	value = readByteFromSPI();
    csconSignal = 1;
	return value;
}
void writeByteToSPI(unsigned char databyte)
{
    unsigned char buffer;
    buffer = SSPBUF;            // Read the buffer to clear any remaining data and clear the buffer full bit
	PIR1bits.SSPIF=0;           // clear SSP interrupt bit
    SSPBUF = databyte;          // Write data byte to the buffer to initiate transmission  	
 	while(PIR1bits.SSPIF == 0);
 	PIR1bits.SSPIF = 0;
}
unsigned char readByteFromSPI(void)
{
 	writeByteToSPI(0x00);
    return SSPBUF; 
}
void RegisterSet(unsigned char adress, unsigned char value)
{
    csconSignal = 0;
    adress = (adress<<1);
    writeByteToSPI(adress);
    writeByteToSPI(value);
    csconSignal = 1;
}
unsigned char RegisterRead(unsigned char adress)
{
	unsigned char value;
    csconSignal = 0;
    adress = ((adress<<1)|0x40);
    writeByteToSPI(adress); 
	value = readByteFromSPI();
    csconSignal = 1;
	return value;
}
unsigned char ReadFIFO(void)
{
	unsigned char value;
    csdataSignal = 0;
	value = readByteFromSPI();
    csdataSignal = 1;
	return value;
}
void WriteFIFO(unsigned char Data)
{
    csdataSignal = 0;
    writeByteToSPI(Data);
    csdataSignal = 1;
}
void SetRFMode(unsigned char mode)
{
	csconSignal = 0;
	unsigned char	mcparam0_read;
	mcparam0_read = transceiverConfigRegisterRead(REG_MCPARAM0);
	switch (mode) {
		case RF_TRANSMITTER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_TRANSMITTER);
			RF_Mode = RF_TRANSMITTER;				//RF in TX mode
			break;
		case RF_RECEIVER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_RECEIVER);
			RF_Mode = RF_RECEIVER;					//RF in RX mode
			break;
		case RF_SYNTHESIZER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SYNTHESIZER);
			RF_Mode = RF_SYNTHESIZER;				//RF in Synthesizer mode
			break;
		case RF_STANDBY:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_STANDBY);
			RF_Mode = RF_STANDBY;					//RF in standby mode
			break;
		case RF_SLEEP:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SLEEP);
			RF_Mode = RF_SLEEP;						//RF in sleep mode
			break;
	} /* end switch (mode) */
	csconSignal = 1;
}
char FindChannel(void)
{
	int cnt = 0;
	isChannelFound = 0;
	
	__delay_ms(1000);
	for (int i = 0; i < 13; i++)
	{	
		transceiverConfigRegisterSet(R1CREG,ChannelR[i]);					//R-value 
		transceiverConfigRegisterSet(P1CREG,ChannelP[i]);					//P-value 
		transceiverConfigRegisterSet(S1CREG,ChannelS[i]);					//S-value 
		transceiverConfigRegisterSet(R2CREG,ChannelR[i]);					//R-value 
		transceiverConfigRegisterSet(P2CREG,ChannelP[i]);					//P-value 
		transceiverConfigRegisterSet(S2CREG,ChannelS[i]);					//S-value 
		transceiverConfigRegisterSet(FTPRIREG,(transceiverConfigRegisterRead(FTPRIREG)|0x02));//Clear PLL_LOCK-flag so we can see it restore on the new frequency
		SetRFMode(RF_SYNTHESIZER);							//Set the transiver to syntesize
		cnt = 0;
		while(cnt < 5)
		{
			
			if((transceiverConfigRegisterRead(FTPRIREG) & 0b00000010) != 0)
			{
				isChannelFound = 1;
				return 1;

			}
			cnt++;
			__delay_us(1000);			
		}
		
		
	}
	return 0;	
}
int isStartTriggerReceived()
{
	if(messageReceivedState == 1)
	{
		messageReceivedState = 0;
		return 1;
	}
	else
		return 0;
}
int isTriggerConfirmationReceived()
{
	if(startTriggerReceivedState == 1)
	{
		startTriggerReceivedState = 0;
		return 1;
	}
	else
		return 0;
}