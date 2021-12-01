/*	Author: Aaron Yang

 *  Partner(s) Name: 

 *	Lab Section:

 *	Assignment: Lab # 5  Exercise # 2

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



unsigned char tempC_num = 0x00;


enum STATES{START, INIT, WAIT ,INCREMENT, DECERMENT, RESET} state;
void Tick(){
	unsigned char pinA_temp = ~PINA & 0x03;
	switch(state){// transitions

	case START:
		
		state = INIT;

		break;

	case INIT:
		tempC_num = 0x07;
		state = WAIT;

		break;

	case WAIT:
		if(pinA_temp == 0x01){
			if(tempC_num < 9){
			tempC_num++;
			}
			state = INCREMENT;
		}
		else if(pinA_temp == 0x02){
			if(tempC_num > 0){
			tempC_num--;
			}
			state = DECERMENT;
		}
		else if(pinA_temp == 0x03){
			tempC_num = 0x00;
			state = RESET;
		}
			
		break;
	case INCREMENT:
		if(pinA_temp == 0x01){
			state = INCREMENT;
		}
		else{
			state = WAIT;
		}
		break;

	case RESET:

		if(pinA_temp == 0x03){
			state = RESET;
		}
		else{
			state = WAIT;
		}
		break;

	case DECERMENT:
		if(pinA_temp == 0x02){
			state = DECERMENT;
		}
		else{
			state = WAIT;
		}

		break;

	default:

		state = WAIT;
		break;

	}

	  switch(state){ //states

		case START:

			break;

		case INIT:
			PORTC = tempC_num;

			break;
		case WAIT:
			PORTC = tempC_num;
			if(pinA_temp == 0x01){
				PORTC += 1;
			}
			break;
		case INCREMENT:
			PORTC = tempC_num;
			break;

		case RESET:
			tempC_num = 0x00;
			PORTC = 0x00;

			break;

		case DECERMENT:
			PORTC = tempC_num;

			break;

                default:
			PORTC = tempC_num;
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

