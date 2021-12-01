/*	Author: Aaron Yang

 *  Partner(s) Name: 

 *	Lab Section:

 *	Assignment: Lab # 7  Exercise # 2

 *	DEMO: https://youtu.be/hdNSFMGV5j4

 *	Exercise Description: [optional - include for your own benefit]

 *

 *	I acknowledge all content contained herein, excluding template or example

 *	code, is my own original work.

 */

#include <avr/io.h>

#include <avr/interrupt.h>

#include "io.h"

#ifdef _SIMULATE_

#include "simAVRHeader.h"

#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
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

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
} 

enum STATES{START, INIT, LED_ONE, LED_TWO, LED_THREE, LED_BACK, BUTTON, RELEASE} state;
unsigned char pointCounter = 0x00;
void Tick(){
	unsigned char buttonMask = ~PINA & 0x01;
	unsigned char pinBMask = PINB & 0x07;
	switch(state){// transitions

	case START:
		state = INIT;
	break;
	case INIT:
		pointCounter = 0x05;
		state = LED_ONE;
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(pointCounter +'0');
	break;
	case LED_ONE:
		if(buttonMask == 0x01){
			state = BUTTON;
		}
		else{
			state = LED_TWO;
		}
	break;
	case LED_TWO:
		if(buttonMask == 0x01){
			state = BUTTON;
		}
		else{
			state = LED_THREE;
		}
	break;
	case LED_THREE:
		if(buttonMask == 0x01){
			state = BUTTON;
		}
		else{
			state = LED_BACK;
		}
	break;
	case LED_BACK:
		if(buttonMask == 0x01){
			state = BUTTON;
		}
		else{
			state = LED_ONE;
		}
	break;
	case BUTTON:
		if(buttonMask == 0x01){
			state = BUTTON;
		}
		else{
			state = RELEASE;
		}
	break;
	case RELEASE:
		if ((buttonMask) == 0x01) {
			if (pointCounter == 0x09) {//accounts for when it is at 9 points, and then reset to 5.
				state = START;
			}
			else { // if not at 9 points continue game.
				state = LED_ONE;
			}
		}
		else {
			state = RELEASE;
		}
	break;
	default:
		state = START;
	break;
	
	}

	switch(state){ //states

	case START:
	break;
	case INIT:
	break;
	case LED_ONE:
		PORTB = 0x01;
	break;
	case LED_TWO:
		PORTB = 0x02;
	break;
	case LED_THREE:
		PORTB = 0x04;
	break;
	case LED_BACK:
		PORTB = 0x02;
	break;
	case BUTTON:
		if (((pinBMask) == 0x02) && (pointCounter < 0x09)) { //if it is at the second LED and the point if less than 9
				pointCounter++; // Increment
				if (pointCounter == 0x09) { // if it is at 9 points, output win message.
					LCD_DisplayString(1, "YOUWIN!");
				}
				else { 
					break;
				}
			}
			else if (((pinBMask) != 0x02) && (pointCounter > 0)) {//else if it is at not at the second LED and more than 0
				pointCounter--; //Decrement
			}
		LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(pointCounter +'0');
	break;
	case RELEASE:
		PORTB = PINB;
	break;
	default:
	break;

        }


}


int main(void) {

     // Insert DDR and PORT initializations  

        DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();

	state = START;

	TimerSet(300);

	TimerOn();

    // Insert your solution below */

        

    while (1) {
	
	Tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }

    return 1;

}

