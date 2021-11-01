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

enum STATES{START, INIT, BUTTON_ONE, BUTTON_TWO, BUTTON_THREE}STATE;

void Tick(){
    unsigned char BUTTON = ~PINA & 0x07;
    switch(STATE){
        case START:
            STATE = INIT;
        break;
        case INIT:
            if(BUTTON == 0x01){
                STATE = BUTTON_ONE;
            }
            else if(BUTTON == 0x02){
                STATE = BUTTON_TWO;
            }
            else if(BUTTON = 0x04){
                STATE = BUTTON_THREE;
            }
            else{
                STATE = INIT;
            }
        break;
        case BUTTON_ONE:
            if(BUTTON == 0x01){
                STATE = BUTTON_ONE;
            }
            else{
                STATE = INIT;
            }
        break;
        case BUTTON_TWO:
            if(BUTTON == 0x02){
                STATE = BUTTON_TWO;
            }
            else{
                STATE = INIT;
            }
        break;
        case BUTTON_THREE:
            if(BUTTON == 0x04){
                STATE = BUTTON_THREE;
            }
            else{
                STATE = INIT;
            }    
        break;
        default:
            STATE = START;
        break;

    }
    switch(STATE){
        case START:
        break;
        case INIT:
             set_PWM(0);
        break;
        case BUTTON_ONE:
            set_PWM(261.63);
        break;
        case BUTTON_TWO:
            set_PWM(293.66);
        break;
        case BUTTON_THREE:
            set_PWM(329.63);
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
