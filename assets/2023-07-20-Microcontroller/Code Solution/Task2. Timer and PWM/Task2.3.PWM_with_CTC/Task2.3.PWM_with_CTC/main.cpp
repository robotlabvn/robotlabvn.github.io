
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DUTY_5_PERCENT 0
#define DUTY_7_5_PERCENT 1

// Global variable 
volatile uint8_t duty = DUTY_5_PERCENT;

int main (void)
{
	/***************************
	Hardware configuration:
	PORT B = Switcher
	PORT D = PIN5 =PWM
	*************************/
	
	DDRD |= (1<<PIND5); //PD5 config PD5 Output to Servo
	
	TCCR1B |= (1<<WGM12)  | (1<<CS11) | (1<<CS10); // WGW12  (Mode 4) , CS11 and CS10 = Prescaler 64.
	TIMSK1 |= (1<<OCIE1A); // Timer 1 Output Compare Match Interrupt Enable
	
	/**********************
	Calculation of the values for the value:
	Value of OCR1A (Counter count up to this value):
	Repetition Rate =50 Hz
	8000000/64(Prescaler)/50(Hz) = 2500
	
	At the duty cycle of 5%:
	2500 *0.95 = 2375 =0x947 LOW
	2500 *0.05 = 125 =0x7D HIGH
	
	At duty cycle of 7.5%:
	2500 * 0.925 = 2313 = 0x909 LOW
	2500 * 0.075 = 187 = 0xBB HIGH
	
	***********************/
	OCR1A = 0x947; // Start value for the period
	sei(); // Enable Global Interrupts

	
	while(1)
	{
		if (!(PINB & (1<<PINB0))) //If button SW0 has been pressed, the variable set to mode 7.5%
		{
				duty= DUTY_7_5_PERCENT;
		}
		else if (!(PINB & (1<<PINB1)))
		{
			duty = DUTY_5_PERCENT;
		}
	}
}

/*******************************
Timer 1 Compare Interrupt triggered when the counter reaches the value OCR1A
*******************************/
ISR(TIMER1_COMPA_vect){ 
	
	if (duty == DUTY_5_PERCENT)  // if the duty cycle set 5% 
	{
		if (OCR1A == 0x947)     // If the overflow level was LOW
		{
			PORTD |= (1<< PIND5);  //Set Pin PD5 to HIGH
			OCR1A = 0x7D;        // set OCR1A to next value to HIGH
		}
		else {
			PORTD &= ~(1<<PIND5); // Set Pin 
			OCR1A = 0x947;
		}
	}
	else if (duty = DUTY_7_5_PERCENT)
	{
		if (OCR1A == 0x909 )
		{
			PORTD |= (1<<PIND5);
			OCR1A = 0xBB;
		}
		else{
			PORTD &= ~(1<<PIND5);
			OCR1A = 0x909;
		}
	}
}
