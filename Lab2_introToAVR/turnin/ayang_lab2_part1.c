/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1){

	if(PINA ==  0x00 ){

		PORTB = 0;

	}
	if(PINA == 0x01){

		PORTB = 1;

	}
	
	if(PINA == 0x02){

		PORTB = 0;

	}

	if(PINA == 0x03){

		PORTB = 0;
	}

    }
    return 1;
}


