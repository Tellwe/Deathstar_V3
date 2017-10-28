#include "transceiver.h"
static BOOL bTransiverModeReceive=FALSE;
void transceiverConfig(){
	TransiverInit();
}

void updateTransceiver(){

	if(!bTransiverModeReceive)
			TransiverToReceive();
	if(trIRQ1 && bTransiverModeReceive)										
			TransiverReadFIFO();	
}

void sendMessage(BYTE topic, BYTE value){
	TransmittPacket(topic, value);
}
int isMessageReceived(){
	
	return 0;
}



//*************************************************************************************
/****************Function description**********************
Function sets the transiver to receive mode
*******************************************************/
void TransiverToReceive()
{
	timerFunction(2, 5); //Set a timeout timer on five seconds for problem with the transiver


	//Cycle for going into RX-mode
	SetRFMode(RF_STANDBY);								//Transiver into Standby
	__delay_ms(10);										//Wait for oscillator to wake up
	RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
	SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
	while((RegisterRead(FTPRIREG) & 0b00000010) == 0)	//PLL Lock
	{
		if(bTimerComplete[2])
		{
			FindChannel();								//If no PLL-lock, find new values for the frequency
			break;
		}
	}
			
	SetRFMode(RF_RECEIVER);
	__delay_us(500);
	bTransiverModeReceive = 1;						
}
/****************Function description**********************
Function reads the fifo from the transiver, and returns the sent data package.
*******************************************************/
void TransiverReadFIFO()
{
	unsigned char ReceivedString[30];//Char string containing the data received from the transiver
	timerFunction(3, 5); //Set a timeout timer on five seconds for problem with the transiver
	
	SetRFMode(RF_STANDBY);
	bTransiverModeReceive = 0;
	int i = 0;
	for (int j = 0; j < 30; ++j)
	{
		ReceivedString[j] = 0;
	}
	while((trIRQ0)&&(!bTimerComplete[3]))										//Read the FIFO from the transiver until the FIFO is empty 
	{
		ReceivedString[i] = ReadFIFO();				//Place bytes in the string for received data
		i++;
	}

	__delay_ms(10);	
	SetRFMode(RF_SLEEP);								//Set the transiver into sleep-mode	

	ReceivedPacketHandler(ReceivedString);
}
/*********************************************************************
*Function for decrypting the package received and handling the data 
*
*
*
*
**********************************************************************/

void ReceivedPacketHandler(unsigned char Data[])
{
	//Backward compatibility for the old transmitters
	//Check data to se what command that has been sent 
	if((strstr(Data, "N1BLINK")) && (OperationMode() == 6))					//Requsted node == 1
	{
		intBlinkCycle = 1;
		intBlinkCounter = 0;
		DelayDs(100);			//Delay between succesfull recived commands
	}
	else if((strstr(Data, "N2BLINK")) && (OperationMode() == 7))				//Requested node == 2
	{
		intBlinkCycle = 1;
		intBlinkCounter = 0;
		DelayDs(100);			//Delay between succesfull recived commands
	}

	//End of backward compatibility

	if(Data[0] != STARTCHAR || Data[3] != ENDCHAR) //Check if the packet is complete and correct
		return;
	
	switch (Data[1])
	{
		case FLASH:
			switch (Data[2])
			{
				case LED1:
					oLEDLight = 1;
					DelayDs(10);
					oLEDLight = 0;
					DelayDs(5);
					break;
		
				case LED2:
					oLEDBlink = 1;
					DelayDs(10);
					oLEDBlink = 0;
					DelayDs(5);
					break;

				case LED3:
					oOnBoardLED = 0;
					DelayDs(10);
					oOnBoardLED = 1;
					DelayDs(5);
					break;

				default:
					break;
					
			}
			break;
		case BUSSIGNAL:
			if(Data[2] == NODE1 && OperationMode() == 6)
			{
				intBlinkCycle = 1;
				intBlinkCounter = 0;
				DelayDs(100);			//Delay between succesfull recived commands
				TransmittPacket(BUSSIGNAL, BLINKSTARTED);
			}
			if(Data[2] == NODE2 && OperationMode() == 7)
			{
				intBlinkCycle = 1;
				intBlinkCounter = 0;
				DelayDs(100);			//Delay between succesfull recived commands
				TransmittPacket(BUSSIGNAL, BLINKSTARTED);
			}
			if(Data[2] == BLINKSTARTED && (OperationMode() == 4 || OperationMode() == 5))
			{
				intBlinkCycle = 1;
				intBlinkCounter = 0;
				DelayDs(100);			//Delay between succesfull recived commands
					
			}
			break;

		case LIGHTSENSVAL:
			if(Data[2] != 0)
				break;
			TransmittPacket(LIGHTSENSVAL, AnalogValue(0));		
			break;

		case POTVAL:
			if(Data[2] != 0)
				break;
			TransmittPacket(POTVAL, AnalogValue(3));		
			break;

		case PROGVAL:
			if(Data[2] != 0)
			{
				eeprom_write(ADDRdarknessValue, Data[2]);
				break;
			}
			TransmittPacket(PROGVAL, eeprom_read(ADDRdarknessValue));
			break;

		case USEPOT:
			if(Data[2] == 0)
			{
				if(bValueFromPot == TRUE)
					TransmittPacket(USEPOT, YES);
				else
					TransmittPacket(USEPOT, NO);
			}
			else if(Data[2] == YES)
				bValueFromPot = TRUE;
			else if(Data[2] == NO)
				bValueFromPot = FALSE;

			break;

		case DARKCALC:
			if(Data[2] != 0)
				break;
			DarknessCheck();
			if(bDark)	
				TransmittPacket(DARKCALC, DARK);
			else
				TransmittPacket(DARKCALC, NOTDARK);
			break;

		case CLEARMEMORY:
			write_ram_status(read_ram_status() & 0b11100011);
			ResetMemoryAdress();
			ram_bulk_erase();
			TransmittPacket(CLEARMEMORY, DONE);
			break;

		case READMEMORY:
			if(!bSaveDataToFlash)  //if save is in progress the memory is allocated for saving
				SendMemoryData();
			else
				TransmittPacket(READMEMORY, NOTDONE);
			break;

		default:
			break;
	}
}
/*********************************************************************
 * void TransmittPacket(char, char)
 *
 * Overview:        
 *              Sends the variable "dataString" through the transiver
 *
 * PreCondition:    
 *              Hardware initiated
 *
 * Input:       
 *              The string to be sent
 *				
 *
 * Output:      
 *
 * Side Effects:    
 *              
 *
 ********************************************************************/
void TransmittPacket(BYTE topic, BYTE value)
{
	timerFunction(4, 5); //Set a timeout timer on five seconds for problem with the transiver
	//Local variables
	int i = 0;

	//Initiation of transmitt sequence
		SetRFMode(RF_STANDBY);								//Transiver into Standby
		__delay_ms(10);										//Wait for oscillator to wake up
		RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear the bit for detection for the PLL Lock
		SetRFMode(RF_SYNTHESIZER);							//Transiver into syntesize
		while((RegisterRead(FTPRIREG) & 0b00000010) == 0)	//Wait for the PLL to lock
		{
			if(bTimerComplete[4])
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
		while(!trIRQ1)
		{
			if(bTimerComplete[4])
			break;
		}
		__delay_us(10);
		SetRFMode(RF_SLEEP);
		__delay_ms(50);

}

//**************************************************************************************
// Send one byte on the SPI
//**************************************************************************************
void WriteSPI(unsigned char databyte)
{
    unsigned char buffer;
    buffer = SSPBUF;            // Read the buffer to clear any remaining data and clear the buffer full bit
	PIR1bits.SSPIF=0;           // clear SSP interrupt bit
    SSPBUF = databyte;          // Write data byte to the buffer to initiate transmission  	
 	while(PIR1bits.SSPIF == 0);
 	PIR1bits.SSPIF = 0;
}
//**************************************************************************************
// Read one byte on the SPI
//**************************************************************************************
unsigned char ReadSPI(void)
{
 	WriteSPI(0x00);
    return SSPBUF; 
}
//**************************************************************************************
// Initiate the transiver
//**************************************************************************************
void TransiverInit(void)
{  
	
	RegisterSet(GCONREG, 0x30);					//Set to the right frequency 
	RegisterSet(DMODREG,(0xA8)); 				//Set transiver into buffer mode
	RegisterSet(FDEVREG, 0x09);	//0x09				//Set the frequency deeviation to 40KHz
	RegisterSet(BRSREG, 0x07);	//0x09				//Set the bitrate to 25kbps	
	RegisterSet(FIFOCREG,(0x0A));				//Set the FIFO-size to 16 bytes and the treshhold for interrupts to 10
	RegisterSet(FTXRXIREG,(0x00|0xB0|0x09));	//IRQ0RX = nFIFOEmpty, IRQ1RX = FIFO_THRESHOLD, IRQ0TX = nFIFOEMPTY, IRQ1TX = TXDONE
	RegisterSet(FTPRIREG,(0x01|0x10|0x01));	//	//Start to till FIFO when sync word is detected, start transmission when FIFO_not_full
	RegisterSet(FILCREG, 0xA3);					//FIltersetting for the transiver
	RegisterSet(SYNCREG,(0x18|0x20|0x06));		//SYNC-word enabled, 32 bit size, 3 errors allowed
	RegisterSet(SYNCV31REG,('S'));				//
	RegisterSet(SYNCV23REG,('Y'));				//
	RegisterSet(SYNCV15REG,('N'));				//
	RegisterSet(SYNCV07REG,('C'));				//
	RegisterSet(TXCONREG, 0x72);			 		//Transmitt parameters
	RegisterSet(CLKOUTREG, 0x3C);					//Dissable CLKOUT
	RegisterSet(FCRCREG, 0x80);
	RegisterSet(GCONREG, (RegisterRead(GCONREG)|0x01));

	if(FindChannel() == 1)
		Blink(LED2, 1);
	SetRFMode(RF_SLEEP);

}
/*********************************************************************
 * WORD FindChannel()
 *
 * Overview:        
 *              The function uses the arrays of valuse calculated for the RPS-valuse in the transiver
 *				and tests these to get the PLL-lock bit OK
 *
 * PreCondition:    
 *              Arrays OK
 *
 * Input:       
 *          None
 *
 * Output:  1 - if OK
 *			0 if NOK    
 *
 * Side Effects: Communication with the transiver   
 *
 ********************************************************************/
char FindChannel(void)
{
	int cnt = 0;
	bChannelFound = 0;
	channelFound = 0;
	
	__delay_ms(1000);
	for (int i = 0; i < 13; i++)
	{	
		RegisterSet(R1CREG,ChannelR[i]);					//R-value 
		RegisterSet(P1CREG,ChannelP[i]);					//P-value 
		RegisterSet(S1CREG,ChannelS[i]);					//S-value 
		RegisterSet(R2CREG,ChannelR[i]);					//R-value 
		RegisterSet(P2CREG,ChannelP[i]);					//P-value 
		RegisterSet(S2CREG,ChannelS[i]);					//S-value 
		RegisterSet(FTPRIREG,(RegisterRead(FTPRIREG)|0x02));//Clear PLL_LOCK-flag so we can see it restore on the new frequency
		SetRFMode(RF_SYNTHESIZER);							//Set the transiver to syntesize
		cnt = 0;
		while(cnt < 5)
		{
			
			if((RegisterRead(FTPRIREG) & 0b00000010) != 0)
			{
				bChannelFound = 1;
				channelFound = i;
				return 1;
			}
			cnt++;
			__delay_us(1000);			
		}
		
		
	}
return 0;	

}
/*********************************************************************
 * void SetRFMode(mode)
 *
 * Overview:        
 *              Sets the transiver to the desired mode
 *
 * PreCondition:    
 *              Hardware initiated
 *
 * Input:       
 *              the desired mode of the transiver
 *				
 *
 * Output:      
 *
 * Side Effects:    
 *              
 *
 ********************************************************************/
void SetRFMode(BYTE mode)
{
	trCSCON = 0;
	BYTE	mcparam0_read;
	mcparam0_read = RegisterRead(REG_MCPARAM0);
	switch (mode) {
		case RF_TRANSMITTER:
			RegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_TRANSMITTER);
			//RF_Mode = RF_TRANSMITTER;				//RF in TX mode
			break;
		case RF_RECEIVER:
			RegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_RECEIVER);
			//RF_Mode = RF_RECEIVER;					//RF in RX mode
			break;
		case RF_SYNTHESIZER:
			RegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SYNTHESIZER);
			//RF_Mode = RF_SYNTHESIZER;				//RF in Synthesizer mode
			break;
		case RF_STANDBY:
			RegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_STANDBY);
			//RF_Mode = RF_STANDBY;					//RF in standby mode
			break;
		case RF_SLEEP:
			RegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SLEEP);
			//RF_Mode = RF_SLEEP;						//RF in sleep mode
			break;
	} /* end switch (mode) */
	trCSCON = 1;
}

/*********************************************************************
 * WORD RegisterRead()
 *
 * Overview:        
 *              This function access the control register of MRF89XA.
 *              The register address and the register settings are
 *              the input
 *
 * PreCondition:    
 *              None
 *
 * Input:       
 *          WORD    setting     The address of the register and its
 *                              corresponding settings
 *
 * Output:  None    
 *
 * Side Effects:    Register settings have been modified
 *
 ********************************************************************/
unsigned char RegisterRead(unsigned char adress)
{
	BYTE value;
    trCSCON = 0;
    adress = ((adress<<1)|0x40);
    WriteSPI(adress); 
	value = ReadSPI();
    trCSCON = 1;
	return value;
}
/*********************************************************************
 * void RegisterSet(BYTE address, BYTE value)
 *
 * Overview:        
 *              This function access the control register of MRF89XA.
 *              The register address and the register settings are
 *              the input
 *
 * PreCondition:    
 *            	 None
 *
 * Input:       
 *          WORD    setting     The address of the register and its
 *                              corresponding settings
 *
 * Output:  None    
 *
 * Side Effects:    Register settings have been modified
 *
 ********************************************************************/
void RegisterSet(unsigned char adress, unsigned char value)
{
    trCSCON = 0;
    adress = (adress<<1);
    WriteSPI(adress);
    WriteSPI(value);
    trCSCON = 1;
}
/*********************************************************************
 * BYTE ReadFIFO(void)
 *
 * Overview:        
 *              The function reads one byte from the FIFO
 *
 * PreCondition:    
 *              MRF89XA transceiver has been properly initialized
 *
 * Input:       
 *              None
 *
 * Output:      Data from FIFO
 *
 * Side Effects:    
 *              The packet has been sent out
 *
 ********************************************************************/
unsigned char ReadFIFO(void)
{
	BYTE value;
    trCSDATA = 0;
	value = ReadSPI();
    trCSDATA = 1;
	return value;
	
}
/*********************************************************************
 * void WriteFIFO(BYTE Data)
 *
 * Overview:        
 *              This function fills the FIFO
 *
 * PreCondition:    
 *              MRF89XA transceiver has been properly initialized
 *
 * Input:       
 *              BYTE   Data - Data to be sent to FIFO.
 *
 * Output:      None
 *
 * Side Effects:    
 *              The packet has been sent out
 *
 ********************************************************************/
void WriteFIFO(unsigned char Data)
{
    trCSDATA = 0;
    WriteSPI(Data);
    trCSDATA = 1;
}
