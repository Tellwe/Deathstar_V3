//Processor and compiler dependant
#include <xc.h>

void initialConfigurationP16F887(){

	// set up oscillator control register
    OSCCONbits.IRCF2 = 1; //set OSCCON IRCF bits to select OSC frequency=4Mhz
    OSCCONbits.IRCF1 = 1; //set OSCCON IRCF bits to select OSC frequency=4Mhz
    OSCCONbits.IRCF0 = 0; //set OSCCON IRCF bits to select OSC frequency=4Mhz
    OSCCONbits.SCS = 1; //set the SCS bits to select internal oscillator block

	//Init ports 
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;

	//Configure ports
	TRISA = 0b00001011; //RA0 and RA1 inputs, RA2, RA4 and RA5 DI on transmitter
	TRISB = 0b00111101; //RB3/AN9 Voltage Battery. RB5, RB1 inputs, RB3 and RB4 connected to transiver 
	TRISC = 0b00010000; //RC4 connected to transiver
	TRISD = 0b00000111; //RD0, RD1, RD2 for the brackets
	TRISE = 0b00000111; //RE1, RE2, RE3 connected to amp and volt measurements
	
	ANSEL = 0b00000000; //Analog select
	ANSELH = 0b00000000; //Analog Select
	ANSELbits.ANS0 = 1;	//RA0 = analog input
	ANSELbits.ANS3 = 1;	//RA3 = analog input
	ANSELbits.ANS5 = 1;	//RE0 = analog input
	ANSELbits.ANS6 = 1;	//RE1 = analog input
	ANSELbits.ANS7 = 1;	//RE2 = analog input
	ANSELHbits.ANS8 = 1;	//RB2 = analog input

	OPTION_REGbits.nRBPU = 0; //For enabling of pull-ups
	WPUBbits.WPUB0 = 1; //Weak pull-up enabled RB0
	while(!RB0);		//Wait for the input to stabilize
	WPUBbits.WPUB5 = 1; //Weak pull-up enabled RB5
	while(!RB5);		//Wait for the input to stabilize
	
	RB1 = 1; //The onboard led has a 1 as off-state

	//Configuration of the SPI communication
	SSPCONbits.SSPM=0x00;       // SPI Master mode, clock = Fosc/4 (1000 Khz)
    SSPCONbits.CKP=0;           // Idle state for clock is low
    SSPSTATbits.CKE=1;          // Transmit occurs on transition from active to idle clock state
    SSPSTATbits.SMP=0;          // Data is sampled at middle of data output time
    SSPCONbits.SSPEN=0x01;      // Enable SPI Port
	SSPIE = 0; //Dectivates the SPI-interrupt
/*
	//Initial values to the SPI Nodes
	trCSDATA = 1; //initial value of CSDATA
	trCSCON = 1; //initial value of CSCON
	csClock = 1;	//Initial value of csClock
	csMem = 1;	//Initial value of csMem

	oOnBoardLED = 1;
*/


	//Configuration of interrupt handler
	INTCONbits.RBIE = 1;	//Enable interrupt when change on PORTB
	INTCONbits.PEIE = 1;	//Enable peripheal interrupts
	PIE1bits.TMR1IE = 1;	//Enable overflow interrupt TMR1
	INTCONbits.GIE = 1;  	//Enable all unmasked interrupts
	IOCBbits.IOCB5 = 1;		//Enable interrupt on change for input RB5

	//Configuration of timers
	T1CON = 0b00110000;
	TMR1H = 0x0B;
	TMR1L = 0xDB;
	T1CONbits.TMR1ON = 1;

	//Initiation of ADC Conversion
	ADCON0bits.ADCS0 = 0;		//ADC Clock source
	ADCON0bits.ADCS1 = 0;		//ADC Clock source
	ADCON1bits.ADFM = 0;		//ADC result left justified
	ADCON1bits.VCFG1 = 0;		//ADC Ref voltage at VSS
	ADCON1bits.VCFG0 = 0;		//ADC Ref voltage at VDD
/*
	//Initiation of variables
	intSecondCounter = 0;
	intHalfSecondCounter = 0;
	intMinuteCounter = 0;
*/
}