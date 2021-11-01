/*    Author: lab
 *  Partner(s) Name:
 *    Lab Section:
 *    Assignment: Lab #  Exercise #
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
void set_PWM(double frequency){
        static double current_frequency;
        if(frequency != current_frequency){
                if(!frequency){ TCCR3B &= 0x08; }
                else {TCCR3B |= 0x03; }

                if(frequency < 0.954){ OCR3A = 0xFFFF; }
                else if(frequency > 31250){ OCR3A = 0x0000; }
                else {OCR3A = (short) (8000000 / (128*frequency)) - 1; }

                TCNT3 = 0;
                current_frequency = frequency;
        }
}

void PWM_on(){
        TCCR3A = (1 << COM3A0);
        TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

        set_PWM(0);
}

void PWM_off(){
        TCCR3A = 0x00;
        TCCR3B = 0x00;
}

double ARRAY[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
enum STATES{START, INIT, WAIT, ON, HOLD, HOLD_RELEASE, PLAY, PITCHUP, WAIT_TWO, PITCHDOWN, WAIT_THREE}STATE;
unsigned char i, COUNTER;

void Tick(){
    unsigned char BUTTON = ~PINA & 0x07;
    switch(STATE){ //transitions
        case START:
            STATE = INIT;
        break;
        case INIT:
            STATE = WAIT;
        break;
        case WAIT:
            if(BUTTON == 0X01){
                STATE = HOLD;
            }
            else{
                STATE = WAIT;
            }
        break;
        case HOLD:
            if(BUTTON == 0x01){
                STATE = HOLD;
            }
            else{
                STATE = ON;
            }
        break;
        case HOLD_RELEASE:
            if(BUTTON == 0x01){
                STATE = HOLD_RELEASE;
            }
            else{
                STATE = WAIT;
            }
        break;
        case ON:
            STATE = PLAY;
        break;
        case PLAY:
            if(BUTTON == 0x01){
                STATE = HOLD_RELEASE;
            }
            if((BUTTON == 0x02) && (i < 7)){
                STATE = WAIT_TWO;
            }
            if((BUTTON == 0x04) && (i > 0)){
                STATE = WAIT_THREE;
            }

        break;
        case PITCHUP:
            STATE = PLAY;
        break;
        case PITCHDOWN:
            STATE = PLAY;
        break;
        case WAIT_TWO:
            if(BUTTON == 0x02){
                STATE = WAIT_TWO;
            }
            else{
                STATE = PITCHUP;
            }
        break;
        case WAIT_THREE:
            if(BUTTON == 0x04){
                STATE = WAIT_THREE;
            }
            else{
                STATE = PITCHDOWN;
            }
        break;
        default:
            STATE = START;
        break;

    }
    switch(STATE){ //states
        case START:
		PWM_off();
        break;
        case INIT:
		set_PWM(0);
        break;
        case WAIT:
		PWM_off();
        break;
        case ON:
		PWM_on();
        break;
        case HOLD:
		i = 0;
        break;
        case HOLD_RELEASE:
        break;
        case PLAY:
		set_PWM(ARRAY[i]);
        break;
        case PITCHUP:
		 if(i < 7){
			++i;
		}
        break;
        case PITCHDOWN:
		if(i > 0){
			--i;
		 }

        break;
        case WAIT_TWO:
        break;
        case WAIT_THREE:
        break;
        default:
        break;
    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0x40; PORTB = 0x00;
    /* Insert your solution below */
        PWM_on();
        STATE = START;
    while (1) {
        Tick();
    }
    return 1;
}

