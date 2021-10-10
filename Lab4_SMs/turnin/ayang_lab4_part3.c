/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4  Exercise # 3
 *
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES{START, INIT, RELEASE_ONE, WAIT, RELEASE_TWO, UNLOCK} state;

void Tick(){
	switch(state){
	case START:
		state = INIT;
		break;
	case INIT:
		if(PINA == 0x04){
			state = RELEASE_ONE;
		}
		else{
			state = START;
		}
		break;
	case RELEASE_ONE:
		if(PINA == 0x04){
			state = RELEASE_ONE;
		}
		else if (PINA == 0x00){
			state = WAIT;
		}
		else{
			state = START;
		}
		break;
	case WAIT:
		if(PINA == 0x02){
			state = RELEASE_TWO;
		}
		else if(PINA == 0x00){

			state = WAIT;

		}
		else{
			state = START;
		}
		break;
	case RELEASE_TWO:
		if(PINA == 0x02){
			state = RELEASE_TWO;
		}
		else{
			state = UNLOCK;
		}
		break;
	case UNLOCK:
		 if(PINA == 0x80){
                        state = START;
                }
                else{
                        state = UNLOCK;
                }
                break;

	default:
		state = INIT;
		break;
	}
	  switch(state){
		case START:
			PORTB = 0x00;
			break;
		case INIT:
			PORTB = 0x00;
		case RELEASE_ONE:
			break;
		case WAIT:
			break;
		case RELEASE_TWO:
			break;
		case UNLOCK:
			PORTB = 0x01;
			break;
                default:
                        break;
        }

}

int main(void) {
     // Insert DDR and PORT initializations  
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;
    // Insert your solution below */
        state = START;
    while (1) {
        Tick();
    }
    return 1;
}
