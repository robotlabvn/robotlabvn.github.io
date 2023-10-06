//#define F_CPU 8000000
#include <avr/io.h>
//#include <util/delay.h>

void program(void); //Create a sub-program1 

int main (void)
{
	program();
	
}
void program(void)
{
	/***********************
	Hardware configuraion:
	PORTD: LED
	***************/
	
	/***********************
	Calculation:
	F_CPU/prescale/5(state change per second) with F_CPU=8 MHz
	A divisor of 256 count to 6250= 0x186A
	200 ms = (1/F_CPU)*256*6250 = 125 ns *256*6250
	***********************/
	uint16_t mark=6250;
	
	DDRD =0xFF;
	PORTD =0xFF;
	TCCR1B |=(1<<CS12); //Set up timer 1: CS12 (clock/256)
	
	while(1)
	{			
		while(TCNT1 == mark)
		{//While loop compare with value
		TCNT1 = 0;
		PORTD ^= (1 << PIND2); // toggle PD2
		}
	}
	
}
void program_2(void)
{
	DDRD= 0xFF;
	PORTD = 0xFF; // Turn off LED
	
	
}
