/*
 * Task4.ADC.Reading.cpp
 *
 * Created: 10/22/2018 7:17:31 AM
 * Author : KNIGHT
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB =0xFF; //setting the PORTB is output
	DDRF =0x00; //setting the PORTF is input
	PORTB =0xFF; // Set LED is turn off
	
	ADMUX |= (1 << MUX0)| (1 << MUX1); //set the ADC channel to 3
	ADMUX |= (1 << REFS0); //set VREF to be source
	ADCSRA |=(1 <<ADEN); //enable ADC
		
    while (1) 
    {	 ADCSRA |= (1 << ADSC); // trigger start ADC Single Conversion
	    while(ADCSRA & (1 << ADSC)); // wait for ADC process to complete
	    PORTB = ~(ADC >> 2); // output 8 MSB ADC to PORTB
	    _delay_ms(100);
    }
}

