/*
* Blink single LED.c
* Created: 8/6/2018 1:44:29 PM
* Author : KNIGHT
*/
//#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//DDRB = (1<<PB4);
	DDRB = 0xff;
	while(1){
		//PORTB = (1<<PB4);
		PORTB = 0xff;
		_delay_ms(1000);
		//PORTB = (0 << PB4);
		PORTB = 0x00;
		_delay_ms(1000);
		
	}
	return 1;
}


