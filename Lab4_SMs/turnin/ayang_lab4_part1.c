/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES{Start, Init, Press_One, Depress_one, Press_two} state;

void Tick(){
	unsigned char buttonTrack = PINA & 0x01;
	unsigned char temp = 0x00;

	switch(state){
	case Start:
		state = Init;
		break;
	case Init:
		if(buttonTrack == 1){
			state = Press_One;
		}
		else{
			state = Init;
		}
		break;
	case Press_One:
		if(buttonTrack == 1){
                        state = Press_One;
                }
                else{
                        state = Depress_one;
                }
                break;
	case Depress_one:
		if(buttonTrack == 1){
                       	state = Press_two;
                }
                else{
                        state = Depress_one;
                }
                break;
	case Press_two:
		 if(buttonTrack == 1){
                        state = Press_two;
                }
                else{
                        state = Init;
                }
                break;
	default:
		state = Init;
		break;
	}
	  switch(state){
                case Init:
                        break;
                case Start:
                        PORTB = 0x01;
                        break;
                case Press_One:
                        PORTB = 0x02;
                        break;
                case Depress_one:
                        break;
                case Press_two:
                        PORTB = 0x01;
                        break;
                default:
			PORTB = 0x01;
                        break;
        }

}

int main(void) {
     // Insert DDR and PORT initializations  
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
    // Insert your solution below */
        state = Start;
    while (1) {
        Tick();
    }
    return 1;
}
