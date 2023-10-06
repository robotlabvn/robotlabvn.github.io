/*
 * Task1_4_SW_and_LED.c
 *
 * Created: 9/20/2018 8:14:25 AM
 * Author : KNIGHT
 */ 

#include <avr/io.h>


int main(void)
{
/* Hardware configuration:
PORT A = free
PORT B ??= LED
PORT C = free
PORT D = push button
*/ uint8_t state = 0;
	DDRD = 0; //  // Data direction PORTD to Input
	DDRB = 0xFF;  //Data direction PORTB on output
    /* Replace with your application code */
    while (1) 
    {
		if (state != PIND)
		{
			state = PIND ;
			PORTB = state;
		}
		
	}
}

