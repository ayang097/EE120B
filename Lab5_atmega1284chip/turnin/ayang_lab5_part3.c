/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 5 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
	unsigned char button = ~PINA & 0x01;

enum STATES {START, INIT, PRESS_ONE, WAIT_ONE, PRESS_TWO, WAIT_TWO, PRESS_THREE} state;

void Tick(){
	switch(state){ //Transitions
		case START:
			state = INIT;
			break;
		case INIT:
			if(button){
				state = PRESS_ONE;
			}
			else{
				state = INIT;
			}
			break;
		case PRESS_ONE:
			if(button){
				state = PRESS_ONE;
			}
			else{
				state = WAIT_ONE;
			}
			break;
		case WAIT_ONE:
			if(button){
				state = PRESS_TWO;
			}
			else{
				state = PRESS_ONE;
			}
			break;
		case PRESS_TWO:
			if(button){
				state = PRESS_TWO;
			}
			else{
				state = WAIT_TWO;
			}
			break;
		case WAIT_TWO:
			if(button){
				state = PRESS_THREE;
			}
			else{
				state = WAIT_TWO;
			}
			break;
		case PRESS_THREE:
			if(button){
				state = PRESS_THREE;
			}
			else{
				state = INIT;
			}
			break;
		default:
			state = INIT;
			break;
	}
	
	switch(state){//States
	case START: 
		break;
	case INIT: 
		PORTB = 0x01;
		break;
	case PRESS_ONE: 
		break;
	case WAIT_ONE:
		PORTB = 0x0F;
		break;
	case PRESS_TWO: 
		break;
	case WAIT_TWO:
		PORTB = 0x12;
		break;
	case PRESS_THREE: 
		break;
	default:
		break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	
	
    /* Insert your solution below */
    while (1) {

	Tick();
    }
    return 1;
}
