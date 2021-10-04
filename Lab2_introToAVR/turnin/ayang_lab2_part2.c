/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 2  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char tempA, tempB, tempC, tempD = 0x00;
	unsigned char cntavail = 4; //since there are 4 different slots; 

	while(1){
		

		tempA = PINA & 0x01; // masking each slot, then counting down cntavail if is true
		tempB = PINA & 0x02;
		tempC = PINA & 0x04;
		tempD = PINA & 0x08;
	
		if(tempA == 0x01){
			cntavail = cntavail - 1;
		}

		if(tempB == 0x02){
                	cntavail = cntavail - 1;
                }
             

		if(tempC == 0x04){
                        cntavail = cntavail - 1;
                }

		if(tempD == 0x08){
                        cntavail = cntavail - 1;
                }

		PORTC = cntavail;

		cntavail = 4; //resets the amount of available slots
	}
	return 1;
}


