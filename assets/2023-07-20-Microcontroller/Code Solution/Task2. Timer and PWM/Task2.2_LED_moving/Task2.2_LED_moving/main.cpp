/*
 * Timer_2.1.c
 *
 * Created: 9/24/2018 7:14:31 AM
 * Author : KNIGHT
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
	
#define LEFT 0
#define RIGHT 1

int main(void)
{
    /* Hardware Configuration
	PORTB = LED */
	DDRB = 0xFF;	//PORTB defines as output
	uint8_t running = 0x01;	//variable stores the state of the running light
	uint8_t direction = LEFT;	//0 = running light to the left, 1 = running light to the right
	
	uint16_t mark=6250;
	
	TCCR1B |=(1<<CS12); //Set up timer 1: CS12 (clock/256)
	
	while(1)	{
		while(direction == LEFT)	{	//running light to the left
			running = (running<<1);	//Variable is shifted 1 bit to the left
			PORTB = ~running;		//output on the LED
			if(running == 0x80)	{//When bit 8th reached, the direction switched to the RIGHT
				direction = RIGHT;
			}
			//_delay_ms(200);		// using delay function OR
			while(TCNT1 <= mark); //While loop compare with value
			TCNT1 = 0;

		}
		while(direction == RIGHT)	{	// running light to the right
			running = (running>>1);
			PORTB = ~running;
			if(running == 0x01)	{
				direction = LEFT;
			}
			//_delay_ms(200);           // using delay function OR
			while(TCNT1 <= mark); //While loop compare with value
			TCNT1 = 0;

		}
	}
}
