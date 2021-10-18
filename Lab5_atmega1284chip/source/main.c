/*	Author: Cindy Ho
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait, BUTN_Press, PB0_ON, PB1_ON, PB2_ON, PB3_ON, PB4_ON, PB5_ON} state;

void Tick() {
	switch(state){//transition
		case Start:
			state = Wait;
			break;
		case Wait:
			if(~PINA ==1) {
				state=BUTN_Press;
			}
			else {
				state=Wait;
			}
			break;
		case BUTN_Press:
			if(~PINA ==1){
				state=PB0_ON;
			}
			else {
				state=Wait;
			}
			break;
		case PB0_ON:
			if (~PINA == 1) {
				state = PB2_ON;
			}
			else {
				state = Wait;
			}
			break;
		case PB1_ON:
			if (~PINA ==1) {
				state = PB3_ON;
			}
			else {
				state = Wait;
			}
			break;
		case PB2_ON:
			if (~PINA ==1) {
				state = PB4_ON;
			}
			else {
				state = Wait;
			}
			break;
		case PB3_ON:
			if (~PINA ==1) {
				state = PB5_ON;
			}
			else {
				state = Wait;
			}
			break;
		case PB4_ON:
			if (~PINA ==1) {
				state = PB1_ON;
			}
			else {
				state = Wait;
			}
			break;
		case PB5_ON:
			if (~PINA ==1) {
				state = PB0_ON;
			}
			else {
				state = Wait;
			}
			break;
	
	}
	switch(state){//state
		case Start:
			PORTB=0;
                        break;
		case Wait:
			PORTB=0;
			break;
		case BUTN_Press:
			break;
                case PB0_ON:
			PORTB=0x01;
                        break;
                case PB1_ON:
			PORTB=0x02;
                        break;
                case PB2_ON:
			PORTB=0x04;
                        break;
                case PB3_ON:
			PORTB=0x08;
                        break;
                case PB4_ON:
			PORTB=0x10;
                        break;
                case PB5_ON:
			PORTB=0x20;
                        break;

	}
}


int main(void) {
/* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	/* Insert your solution below */
	PORTB = 0x00;
	state = Start;
    while (1) {
	Tick();
    }
    return 1;
}
