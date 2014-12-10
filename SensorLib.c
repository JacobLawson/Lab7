//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "SensorLib.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short Left;										// Just to analyze the values
	unsigned short Right;										// index into sample array
	unsigned short Center;


	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;


	while(1) {

short goLeft(){

	// Configure P1.4 to be the ADC input for the Left

		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;		 								// Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		Left = ADC10MEM;										// collect that 10-bit value
}


short goRight(){

	// Configure P1.5 to be the ADC input for Right

		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_5 | ADC10DIV_3 ;						// Channel 3, ADC10CLK/4
		ADC10AE0 = BIT5;		 								// Make P1.3 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		Right = ADC10MEM;									// collect that 10-bit value
}

short goCenter(){

		// Configure P1.3 to be the ADC input for Center

		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_3 | ADC10DIV_3 ;						// Channel 3, ADC10CLK/4
		ADC10AE0 = BIT3;		 								// Make P1.3 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		Center = ADC10MEM;									// collect that 10-bit value
}


		if (Right > 0x0200)	{
			P1DIR = BIT6;
			P1OUT |= BIT6;
		}  else	P1OUT &= ~BIT6;

		if (Left > 0x0200){
			P1DIR = BIT0;
			P1OUT |= BIT0;
		}  else	P1OUT &= ~BIT0;

		if (Center > 0x0200){
			P1DIR = BIT0|BIT6;
			P1OUT |= BIT0|BIT6;
		}  else	P1OUT &= ~BIT0|~BIT6;



	} // end infinite loop

} // end main


