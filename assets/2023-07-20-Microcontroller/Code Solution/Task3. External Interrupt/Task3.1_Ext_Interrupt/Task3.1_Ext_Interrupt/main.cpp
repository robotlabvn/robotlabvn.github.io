/*
 * Interrupts.c
 *
 * Created: 8/13/2018 1:10:24 PM
 * Author : KNIGHT
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t counter =0;
ISR (INT0_vect) //The ISR() function is a general interrupt service routine
{
	counter ++;
}

ISR (INT1_vect)
{
	counter --;
}
int main(void)
{	DDRB =0xFF;
	EICRA = (1 <<ISC11) | (1 <<ISC10) | (1 << ISC00) | (1 << ISC01); // set INT0 and 1 rising edge
	EIMSK = (1 <<INT0)|(1<<INT1); // External Interrupt Enable INT0 and INT1
	sei(); //enable global interrupts
    while (1) 
    {
		PORTB=~counter;
    }
}
