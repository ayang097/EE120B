/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 3  Exercise # 5
 *	Exercise Description: [optional - include for your own benefit]
 *	(Challenge): A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on the micro=controller. 
	If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. 
	If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1.
	 (Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger).
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0x00; PORTD = 0xFF;
        DDRB = 0xFE; PORTB = 0x01;

	unsigned char temp = 0x00;
	unsigned char temp2 = 0x00;
	unsigned short weightSensor = 0x00;
    /* Insert your solution below */
    while (1) {
   
    	temp = PIND << 1;
        temp2 = PINB  & 0x01;

        weightSensor = temp + temp2;

        if(weightSensor < 0x46 && weightSensor > 0x05){

                PORTB = 0x04;

        }

        else if(weightSensor){
                PORTB = 0x02;
	}

    }
    return 1;
}
