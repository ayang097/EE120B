/*	Author: aARON YNAG
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 8 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *      DEMO: https://youtu.be/WtilxY024Gg
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
        ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
        DDRD = 0xFF; PORTD = 0x00;
        ADC_init();
    /* Insert your solution below */
    while (1) {
        unsigned short ADC_TEMP = ADC;
        unsigned char temp = (char)ADC_TEMP;
        unsigned char temp1 = (char)(ADC_TEMP >> 8);
        unsigned char temp2 = temp1 & 0x03;
        PORTB = temp;
        PORTD = temp2;
    }
    return 1;
}
