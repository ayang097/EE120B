/*	Author: Aaron Yang

 *  Partner(s) Name: 

 *	Lab Section:

 *	Assignment: Lab # 7  Exercise # 1

 *	DEMO:https://youtu.be/rvI16-JgmWc

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


unsigned char tempB_num = 0x00;
unsigned char Counter = 0x00;

enum STATES{START, INIT, WAIT ,INCREMENT, DECERMENT, RESET} state;

void Tick(){
	unsigned char pinA_temp = ~PINA & 0x03;
	switch(state){// transitions

	case START:
		state = INIT;
		break;
	case INIT:
		state = WAIT;
		break;
	case WAIT:
		tempB_num = 0;
		if(pinA_temp == 0x01){
			if(Counter < 0x09){
                        	Counter++;
                        }
			state = INCREMENT;
		}
		else if(pinA_temp == 0x02){
			if(Counter > 0x00){
				Counter--;
			}
			state = DECERMENT;
		}
		else if(pinA_temp == 0x03){
			state = RESET;
		}
		else{
			state = WAIT;
		}
		break;
	case INCREMENT:
		if(pinA_temp == 0x01){
			tempB_num++;
			state = INCREMENT;
		}
		else if(pinA_temp == 0x03){
			Counter = 0x00;
			state = RESET;
		}
		else{
			state = WAIT;
		}
		break;
	case RESET:
		if(pinA_temp == 0x03){
			state = RESET;
                } 
		else if(pinA_temp == 0x01){
			state = INCREMENT;
                } 
		else if(pinA_temp == 0x02){
			state = DECERMENT;
                } 
		else {
			state = START;
                }
                        break;
	case DECERMENT:
		if(pinA_temp == 0x02){
			tempB_num++;
			state = DECERMENT;
                } 
		else if(pinA_temp == 0x03){
			Counter = 0x00;
			state = RESET;
                } 
		else {
			state = WAIT;
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
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(PINB+'0');
		break;
	case WAIT:
		PORTB = Counter;
		break;
	case INCREMENT:
		if(tempB_num == 0x0A && Counter < 0x09){
                                Counter++;
                                tempB_num = 0x00;
                        }
                        PORTB = Counter;
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(PINB+'0');
                        break;
		break;
	case RESET:
		Counter = 0x00;
                PORTB = 0x00;
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(PINB+'0');
		break;
	case DECERMENT:
		if(tempB_num == 0x0A && Counter > 0x00){
                                Counter--;
                                tempB_num = 0x00;
                        }
                        PORTB = Counter;
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(PINB+'0');
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

	TimerSet(100);

	TimerOn();

    // Insert your solution below */

        

    while (1) {
	
	Tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }

    return 1;

}

