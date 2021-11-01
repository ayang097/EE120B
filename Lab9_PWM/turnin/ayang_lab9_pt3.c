/*    Author: AARON YANG
 *  Partner(s) Name:
 *    Lab Section:
 *    Assignment: Lab # 9  Exercise # 3
 *    Exercise Description: [optional - include for your own benefit]
 *	demo: https://youtu.be/V6agRXWsTk4
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
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
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerISR()
{
    TimerFlag = 1;
}

void TimerOff()
{
    TCCR1B = 0x00;
}

void TimerOn()
{
    TCCR1B = 0x0B;

    OCR1A = 125;

    TIMSK1 = 0x02;

    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;

    SREG |= 0x80;

}

ISR(TIMER1_COMPA_vect)
{
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0)
    {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M)
{
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

double ARRAY[18] = {293.66, 293.66, 293.66, 440, 392.00, 392.00, 349.23, 293.66, 349.23, 392.00, 261.63, 261.63, 293.66, 440, 392.00, 392.00, 349.23, 293.66};
enum STATES{START, OFF, PLAY, FINISH, HOLD}STATE;
unsigned char i, COUNTER;

void Tick(){
    unsigned char BUTTON = ~PINA & 0x01;
    switch(STATE){ //transitions
	case START:
		STATE = OFF;
	break;
	case OFF:
		if(BUTTON == 0x01){
			STATE = PLAY;
		}
		else{
			STATE = OFF;
		}
	break;
	case PLAY:
		if(i < 18){
 			STATE = PLAY;
		}
		else{
			STATE = FINISH;
		}
	break;
	case FINISH:
		STATE = HOLD;
	break;
	case HOLD:
		if(BUTTON == 0x01){
			STATE = FINISH;
		}
		else{
			STATE = START;
		}
        default:
            STATE = START;
        break;

    }
    switch(STATE){ //states
	case START:
		i = 0;
		set_PWM(0);
	break;
	case OFF:
	break;
	case PLAY:
		set_PWM(ARRAY[i]);
		i++;
	break;
	case FINISH:
		set_PWM(0);
		i = 0;
	break;
	case HOLD:
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
	TimerSet(200);
        TimerOn();
        PWM_on();
        STATE = START;
    while (1) {
        Tick();
	while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}

