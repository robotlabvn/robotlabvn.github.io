#include <avr/io.h>

int main(void)
{ 
	/* Hardware Configuration
	PORT B = LED
	PORT D = Switch
	*/

	uint8_t sum = 0, edgeSW0 = 0, stateSW0 = 0, edgeSW7 = 0, stateSW7 = 0;
	DDRB = 0xFF;		//Configuration PORT B is output
	DDRD = ~((1<<PIND0) | (1<<PIND7)); //Data direction PORTD: PIND0 and PIND7 on input. Does not necessarily have to be set because DDRD = 0
       //Or DDRD = 0B011111110
	
	while(1)   {

		if(PIND & (1<<PIND0))	{       //Button detection SW0=1
			edgeSW0 = 1;
			if(edgeSW0 != stateSW0)	{//Rising Edge detection 
				sum++;		       // Increment counter
			}
			stateSW0 = edgeSW0;		// Equate the variables for the next edge
		}
		else	{
			edgeSW0 = 0;
			stateSW0 = 0;
		}
		if(PIND & (1<<PIND7))	{
			edgeSW7 = 1;
			if(edgeSW7 != stateSW7)	{
				sum--;
			}
			stateSW7 = edgeSW7;
		}
		else	{
			edgeSW7 = 0;
			stateSW7 = 0;
		}
		PORTB = ~sum;
	}
	return 1;
}
