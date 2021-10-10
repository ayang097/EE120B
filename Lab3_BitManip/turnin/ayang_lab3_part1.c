/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 3  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k){
        return ((x & (0x01 << k)) != 0 );
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char portA_temp = 0x00;
	unsigned char portB_temp = 0x00;
	
	unsigned char portA_count = 0x00;
	unsigned char portB_count = 0x00;

    /* Insert your solution below */
    while (1) {	
	portA_count = 0;
	portB_count = 0;

	portA_temp = PINA;
	portB_temp = PINB;

	for(unsigned char i = 0; i < 7; i++){
	
		if(GetBit(tempA, i)){
				
		portA_count++;

		}

		if(GetBit(portB_temp, i)){

		portB_count++;

		}
	}
    }
    return 1;
}
