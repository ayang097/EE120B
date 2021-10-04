/*	Author: Aaron Yang
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 2  Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg.  The remaining 6 bits on D should display an approximation of the total combined weight.
*
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;

	unsigned char weight_one, weight_two, weight_three = 0x00;
	unsigned char weightDifference = 0x00; //for when C - A > 80kg;
	unsigned char sensorCheckD = 0x00;
	unsigned short totalWeight = 0x0000; //Weight_One + Weight_Two + Weight_Three;
	unsigned short totalWeightShift = 0x0000;
	while(1){
		weight_one = PINA;
		weight_two = PINB;
		weight_three = PINC;

		weightDifference = 0x00;

		totalWeight = weight_one+ weight_two + weight_three;

		if(totalWeight > 0x008C){ //checks if total weight is over 140
			sensorCheckD = 0x01; //sets PD0 to 1
		}
		else{
			sensorCheckD = 0x00; //PD to 00;
		}
		if(weight_three <  weight_one){
			if((weight_one - weight_three) > 0x50){//Checks if weight 1 and weight 2 is over 80kg sets PD1 to 1 if true;
				weightDifference = 0x02; //sets PD1 to 1;
			}
			else if((weight_three - weight_one) > 0x50){
				weightDifference = 0x02; //sets PD1 to 1;
			}
		}
	
	
		totalWeightShift = ((totalWeight & 0x00FC)) >> 2; // mask totalWeight with 1111 1100, for PD1 and PD0, then shift;

		PORTD =	(totalWeightShift | sensorCheckD | weightDifference);
		
		weightDifference = 0x00;

		sensorCheckD = 0x00;
	}

	return 1;
}


