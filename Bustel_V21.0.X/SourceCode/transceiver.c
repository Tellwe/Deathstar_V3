#include "transceiver.h"
#include <xc.h>

//Driver for the Transceiver 

//Control signals for the transceiver
#define irqoSignal		RB3
#define irq1Signal		RB4
#define csconSignal		RA4
#define csdataSignal	RA5


void transceiverConfig(){

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
}

void transceiverUpdate(){

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
void SetRFMode(unsigned char mode)
{
	csconSignal = 0;
	unsigned char	mcparam0_read;
	mcparam0_read = transceiverConfigRegisterRead(REG_MCPARAM0);
	switch (mode) {
		case RF_TRANSMITTER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_TRANSMITTER);
			//RF_Mode = RF_TRANSMITTER;				//RF in TX mode
			break;
		case RF_RECEIVER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_RECEIVER);
			//RF_Mode = RF_RECEIVER;					//RF in RX mode
			break;
		case RF_SYNTHESIZER:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SYNTHESIZER);
			//RF_Mode = RF_SYNTHESIZER;				//RF in Synthesizer mode
			break;
		case RF_STANDBY:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_STANDBY);
			//RF_Mode = RF_STANDBY;					//RF in standby mode
			break;
		case RF_SLEEP:
			transceiverConfigRegisterSet(REG_MCPARAM0, (mcparam0_read & 0x1F) | RF_SLEEP);
			//RF_Mode = RF_SLEEP;						//RF in sleep mode
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