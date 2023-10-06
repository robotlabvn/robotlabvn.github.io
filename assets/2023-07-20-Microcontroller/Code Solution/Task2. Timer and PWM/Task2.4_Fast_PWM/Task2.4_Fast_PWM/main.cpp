/*
 * Task2.4_Fast_PWM.cpp
 *
 * Created: 10/5/2018 3:14:35 AM
 * Author : KNIGHT
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define duty_cycle_5_percent 0
#define duty_cycle_50_percent 1

// Global variable for toggling the duty cycle.
volatile uint8_t duty_cycle = duty_cycle_5_percent;

// Global variable for toggling the duty cycle.
/********** Hardware configuration
PORT D= PIN D5= PWM
***********************/
void Fast_PWM(void);

int main(void)
{
  Fast_PWM();
}

void Fast_PWM(void)
{
	DDRB |= (1<<PINB5); // Set Pin D5 is Output
	TCCR1A |= (1<<WGM11) | (1<<COM1A1); // WGM11, 12, 13 = Fast PWM (Mode 14). COM1A1 = Set pin on Compare Match
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) ; // using ICR1 as TOP and Prescaler 8
	/************************************************* ******************************************
	Calculation of the values ??for the counter value:
	Value for ICR1 (Counter counts up to this value):
	Repetition rate = 50 Hz
	16000000 (bars) / 8 (prescaler) / 1000 (Hz repetition rate) = 2000

	Period 
	ICR1 = 2000 = 0x7D0
	
	At a duty cycle of 5%:
	2000 * 0.05 = 100 = 0x64 -Duty Cycle

	At duty cycle of 50%:
	2000 * 0.5 = 1000 = 0x3E8 -Duty Cycle
	**************************************************/
	
	ICR1 = 0x7D0; // start value for the period
	OCR1A = 0x64; // Start value for the duty cycle

	
	while(1){
		if(!(PIND & (1<<PIND0))){
			duty_cycle = duty_cycle_5_percent;
		}
		else if(!(PIND & (1<<PIND1))){
			duty_cycle = duty_cycle_50_percent;
		}
		switch(duty_cycle){
			case duty_cycle_5_percent:
			OCR1A = 0x64; // value for the duty cycle
			break;
			case duty_cycle_50_percent:
			OCR1A = 0x3E8; // value for the duty cycle
			break;
			default:
				break;
		}
		
	}
}

