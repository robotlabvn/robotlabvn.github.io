/*
 * Task3.3LCD_Tick.c
 *
 * Created: 11/12/2018 10:27:47 AM
 * Author : RobotLab
 */ 
//#define  F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd/lcd.h"

uint8_t counter =0;

	/***************************
	Hardware configuration:
	PORT B = LED
	PORT D = SWITCHER (PD0? increment and PD1 ? Decrement)
	*************************/

ISR (INT0_vect) //The ISR() function is a general interrupt service routine
{
	counter ++;
}

ISR (INT1_vect)
{
	counter --;
}
void program1(void);

int main(void)
{		
	DDRB =0xFF;
	EICRA = (1 <<ISC11) | (1 <<ISC10) | (1 << ISC00) | (1 << ISC01); // set INT0 and 1 rising edge
	EIMSK = (1 <<INT0)|(1<<INT1); // External Interrupt Enable INT0 and INT1
	sei(); //enable global interrupts
    while (1) 
    {
		program1();
    }
}

void program1(void)
{
	char Output[20];
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("COUNTER_VALUE: ");
	dtostrf(counter, 2, 1, Output);// 
	lcd_puts(Output);
	PORTB=~counter;
}