/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  6 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	demo: https://youtu.be/K2uf5EMIIuQ
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#endif
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr= 0;

enum STATES {START, LED_ONE, LED_TWO, LED_THREE, LED_BACK,LED_STOP} state;
unsigned char tempB = 0x00;

void TimerOn(){
TCCR1B = 0x0B;
OCR1A = 125;
TIMSK1 = 0x02;
TCNT1 = 0;
_avr_timer_cntcurr = _avr_timer_M;
SREG |= 0x80;
}

void TimerOff() {
  TCCR1B = 0x00;
}
void TimerISR() {
  TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


void Tick(){
	switch(state){//transitions
		case START:

		if((~PINA & 0x01) == 1){
				state = LED_STOP;
			}
			else{
				state = LED_ONE;
			}

		break;

		case LED_ONE:
			if((~PINA & 0x01) == 1){
				state = LED_STOP;
			}
			else{
				state = LED_TWO;
			}
		break;

		case LED_TWO:
			if((~PINA & 0x01) == 1){
				state = LED_STOP;
			}
			else{
				state = LED_THREE;
			}
		break;
	
		case LED_THREE:
			if((~PINA & 0x01) == 1){
				state = LED_STOP;
			}
			else{
				state = LED_BACK;
			}
		break;
		case LED_BACK:
			if((~PINA & 0x01) == 1){
				state = LED_STOP;
			}
			else{
				state = LED_ONE;
			}
		break;

		case LED_STOP:
			if((~PINA & 0x01) == 1){ 
				state = START;
			}
			else{
				state = LED_STOP;
			}
			
		break;
	}

	switch(state){//states

		case START:
		break;
		case LED_ONE:
			tempB = 0x01;
		break;
		case LED_TWO:
			tempB = 0x02;
		break;
		case LED_THREE:
			tempB = 0x04;
		break;
		case LED_BACK:
			tempB = 0x02;
		break;
		case LED_STOP:
			tempB = tempB;
		break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
    	PORTA = 0xFF;	
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	state = START;

    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag){
		
	}
	PORTB = tempB;
	TimerFlag = 0;
    }
    return 1;
}
