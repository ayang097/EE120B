/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 8 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	DEMO: https://youtu.be/KGFBDg4xE60
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

	unsigned short max = 300; // Got the value by looking at the lit up LED's then computing the value from it
	unsigned short min = 17; // same way i got max, but with lowest amount of light possible.
	unsigned short value_compare = max/8;
        
    /* Insert your solution below */
    while (1) {
	
        unsigned short ADC_TEMP = ADC;
        //unsigned char temp = (char)ADC_TEMP;
        //unsigned char temp1 = (char)(ADC_TEMP >> 8);
        //unsigned char temp2 = temp1 & 0x03;
        //PORTB = temp;
        //PORTD = temp2;
	if(ADC_TEMP <= value_compare){
                PORTB = 0x01;
		} 
	else if(ADC_TEMP <= value_compare*2){
                PORTB = 0x03;
		} 
	else if(ADC_TEMP <= value_compare*3){
                PORTB = 0x07;
		} 
	else if(ADC_TEMP <= value_compare*4){
                PORTB = 0x0F;
		} 
	else if(ADC_TEMP <= value_compare*5){
                PORTB = 0x1F;
		} 
	else if(ADC_TEMP <= value_compare*6){
                PORTB = 0x3F;
		} 
	else if(ADC_TEMP <= value_compare*7){
                PORTB = 0x7F;
		} 
	else if(ADC_TEMP <= value_compare*8){
                PORTB = 0xFF;        
		} 
	else {
                PORTB = 0x00;
	}
    }
    return 1;
}
