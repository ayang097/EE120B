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

enum STATES{START, INIT, INCREMENT, DECERMENT, RESET} state;
unsigned char tempC_num = 0x00;
void Tick(){
	switch(state){
	case START:
		state = INIT;
		break;
	case INIT:
		if(PINA == 0){
			state = RESET;
	}
		else if(PINA == 1){
			state = INCREMENT;
	}
		else if(PINA == 2){
			state = DECERMENT;
	}
		else{
			state = INIT;
	}
		break;
	case INCREMENT:
		state = INIT;
		break;
	case RESET:
		state = INIT;
		break;
	case DECERMENT:
		state = INIT;
		break;
	default:
		state = INIT;
		break;
	}
	  switch(state){
		case START:
			break;
		case INIT:
			break;
		case INCREMENT:
			if(tempC_num < 9){
				tempC_num++;
			}
			break;
		case RESET:
			tempC_num = 0;
			break;
		case DECERMENT:
			if(tempC_num > 0 ){
				tempC_num--;
		}
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
	tempC_num = 7;
    while (1) {
	tempC_num = 7;
        Tick();
    }
    return 1;
}
