#include "transceiver.h"
#include <xc.h>
#include <string.h>

//Driver for the Transceiver 
//Variables for the transceiver
static int wirelessId = 0;
static int startTriggerReceivedState = 0;
static int messageReceivedState = 0;
static int RF_Mode = RF_STANDBY;
static int driverUpdateState = 0;
static int transceiverActive = 0;
static int bOkToTransmitt = 0;
static unsigned int *localMilliSecondCounterPtr;
static unsigned int delayTS = 0;
static unsigned int lastMessageReceivedTS = 0;
static unsigned int timeoutTransmissionTS = 0;
static unsigned char transmissionBuffer[10][2] = {
												{0,0},
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0},	
												{0,0}	
};
static unsigned int itemsInTransmissionBuffer = 10; //The same as the number of rows in the transmissionBuffer



void transceiverConfig(transceiverNode_type transceiverNode, int isTransceiverActive, unsigned int *milliSecondCounterPtr)
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

	switch (transceiverNode)
	{
		case NODE1:
			wirelessId = 1;
			break;
		case NODE2:
			wirelessId = 2;
			break;
		case NODE3:
			wirelessId = 3;
			break;
		case NODE4:
			wirelessId = 4;
			break;
	}

	transceiverActive = isTransceiverActive;
	if(transceiverActive)
	{
		driverUpdateState = 1;
		bOkToTransmitt = 1;
	}
		
}
void transceiverUpdate()
{

	//Is the driver in receive mode and not having transmittion active?
	if(driverUpdateState <= 10 && RF_Mode != RF_RECEIVER && transceiverActive)
	{
	//NO, then go into receive mode	
		if(driverUpdateState == 1){
			SetRFMode(RF_STANDBY);
			driverUpdateState = 2;
			delayTS = *localMilliSecondCounterPtr;
		}
		if(driverUpdateState == 2){
			if(*localMilliSecondCounterPtr - delayTS > 10){
				RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
				SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
				delayTS = *localMilliSecondCounterPtr;
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
			else if(*localMilliSecondCounterPtr - delayTS > 5000)
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
	//Yes, the driver is in receive mode

	//Is there data received on the transceiver?
	if(irq1Signal && RF_Mode == RF_RECEIVER)
	{	
	//Yes, there is data avaliable	
		unsigned char Data[30];//Char string containing the data received from the transiver
		delayTS = *localMilliSecondCounterPtr;
		SetRFMode(RF_STANDBY);
		int i = 0;
		for (int j = 0; j < 30; ++j)
		{
			Data[j] = 0;
		}
		while(irqoSignal && *localMilliSecondCounterPtr - delayTS < 4000)		//Read the FIFO from the transiver until the FIFO is empty 
		{
			Data[i] = ReadFIFO();														//Place bytes in the string for received data
			i++;
		}
		SetRFMode(RF_SLEEP);															//Set the transiver into sleep-mode	
		//Backward compatibility for the old transmitters
		//Check data to se what command that has been sent 
		if((strstr(Data, "N1BLINK")) && (wirelessId == 1))								//Requsted node == 1
		{
			messageReceivedState = 1;		
			lastMessageReceivedTS = *localMilliSecondCounterPtr;							//TS to make sure that new message is not sent to soon after message received.
			bOkToTransmitt = 0;
		}
		else if((strstr(Data, "N2BLINK")) && (wirelessId == 2))							//Requested node == 2
		{
			messageReceivedState = 1;
			lastMessageReceivedTS = *localMilliSecondCounterPtr;							//TS to make sure that new message is not sent to soon after message received.
			bOkToTransmitt = 0;
		}
		//End of backward compatibility

		if(Data[0] == STARTCHAR && Data[3] == ENDCHAR)
		{
			if(Data[1] == BUSSIGNAL)
			{
				if((Data[2] == NODE1 && wirelessId == 1) || (Data[2] == NODE2 && wirelessId == 2) || (Data[2] == NODE3 && wirelessId == 3) || (Data[2] == NODE4 && wirelessId == 4))
					messageReceivedState = 1;
			} 
			lastMessageReceivedTS = *localMilliSecondCounterPtr;							//TS to make sure that new message is not sent to soon after message received.
			bOkToTransmitt = 0;
		}
	}
	//No, there is no data received

	//Has there been enough time to send new data since the last received message?
	if((*localMilliSecondCounterPtr - lastMessageReceivedTS > 1000) && (bOkToTransmitt == 0))
	{
		bOkToTransmitt = 1;
	}
	//Is there data to send?
	if(isDataToSend() == 1 || driverUpdateState >= 10)
	{ //Yes, there is data to send
		int i = 0;

		//1000ms since message received?
		if(bOkToTransmitt == 1 && driverUpdateState < 10)
		{
			//Initiation of transmitt sequence
			SetRFMode(RF_STANDBY);								//Transiver into Standby
			delayTS = *localMilliSecondCounterPtr;
			driverUpdateState = 10;
		}
		if(driverUpdateState == 10)
		{
			if(*localMilliSecondCounterPtr - delayTS > 10)
			{
				RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
				SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 11;
			}
			else
			{
				return;
			}
		}
		if(driverUpdateState == 11)
		{
			if((RegisterRead(FTPRIREG) & 0b00000010) == 0)	//Wait for the PLL to lock
			{
				SetRFMode(RF_TRANSMITTER);							//Set the transiver into tranmitt mode
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 12;
			}
			else if(*localMilliSecondCounterPtr - delayTS > 4000)
			{
				FindChannel();
				SetRFMode(RF_TRANSMITTER);							//Set the transiver into tranmitt mode
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 12;
			}
		}
		if(driverUpdateState == 12)
		{
			if(*localMilliSecondCounterPtr - delayTS > 1)
			{
				WriteFIFO('S');
				WriteFIFO('Y');
				WriteFIFO('N');
				WriteFIFO('C');
				//Transmitt data packet
				WriteFIFO(STARTCHAR);
				WriteFIFO(transmissionBuffer[0][0]);
				WriteFIFO(transmissionBuffer[0][1]);
				WriteFIFO(ENDCHAR);	

				//Delete from transmission buffer
				transmissionBuffer[0][0] = 0;
				transmissionBuffer[0][1] = 0;

				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 13;	

			}
			else
			{
				return;
			}
		}
		if(driverUpdateState == 13)
		{
			if(irq1Signal)
			{
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 14;
			}
			else if(*localMilliSecondCounterPtr - delayTS > 4000)
			{
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 14;
			}
			else
			{
				return;
			}
		}
		if(driverUpdateState == 14)
		{
			if(*localMilliSecondCounterPtr - delayTS > 1)
			{
				SetRFMode(RF_SLEEP);
				delayTS = *localMilliSecondCounterPtr;
				driverUpdateState = 15;
			}
			else
			{
				return;
			}
		}
		if(driverUpdateState == 15)
		{
			if(*localMilliSecondCounterPtr - delayTS > 15)
			{
				driverUpdateState = 1;
			}
		}		
	}

//*******************************************OLD*******************************************	
}
int isDataToSend()
{
	if(transmissionBuffer[0][0] != 0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
void sendData(unsigned char topic, unsigned char value)
{
	transmissionBuffer[0][0] = topic;
	transmissionBuffer[0][1] = value;
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