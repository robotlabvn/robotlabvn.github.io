/*
 * Task3.2_External_Interrupt.c
 *
 * Created: 11/12/2018 9:42:05 AM
 * Author : RobotLab
 */ 
//#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t counter =0;
uint16_t mark;
uint8_t flag;

uint16_t tick;


ISR (INT0_vect)
{
	tick ++;
}
ISR (INT1_vect)
{
	flag =0;
}

int main(void)
{
    DDRB = 0xFF;
	PORTB =0xFF;
	TCCR1B |=(1<<CS12);
	
	EICRA = (1<<ISC11)|(1<<ISC10)|(1<<ISC00)|(1<<ISC01);  //set INT0 and 1 rising edge
	EIMSK =(1<<INT0)|(1<<INT1);
	sei();
	
    while (1) 
    {	
		if (flag ==0)
		{
			while(TCNT1 == mark)
			{
				TCNT1 = 0;
				PORTB ^= (1 << PINB2);
			}
		}
		else if (flag == 1)
		{
			PORTB = 0xFF;
		}
		
    }
}

