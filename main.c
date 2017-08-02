#include <p18f4520.h>
#include "lcd.h"
#include <delays.h>
#include <stdio.h>		// sprintf() library
#include <stdlib.h>		// atoi(),atof() library 
#include <usart.h>
#include <capture.h>
#include <timers.h>
#include "MFRC522-RFID-SPI.h"



#define SW1  PORTAbits.RA4
#define SW2  PORTAbits.RA5
#define SW3  PORTCbits.RC0
#define SW4  PORTCbits.RC1


#pragma config OSC = INTIO67
#pragma config PBADEN=OFF

extern void _startup( void ); // See c018i.c in your C18 compiler dir 
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800 
void _reset( void ) 
{ 
    _asm goto _startup _endasm 
} 




void deley_test(){
	long int i;
	for(i = 0; i < 32000; i++){}

}

void main(){
	int x; 
	char str[16] = "Teste RFID: ";
	OSCCON=0b01100010;
	ADCON1=0x0F;
	TRISB = 0b11111110;

	CMCON=7;
	TRISA=0X30;		//RA4,RA5 ARE INPUTS (DIP SWITCHES)
	TRISC=0X0F;		//RC0,RC1 ARE INPUTS (DIP SWITCHES)

	lcd_configura();
	lcd_inicializa();



	printj(str);
while(1)
	{
		if(SW1==0)
		{
			showSerialNumber();			//reads serial number and transmit to serial port
		}
		if(SW2==0)
		{
			readDataHEX();				//reads all memory in tag (64 lines) and transmits to serial in hex
		}
		if(SW3==0)
		{
			readDataASCII();			//reads all tag (64 lines) and transmits to serial in ASCII
		}
	}


}