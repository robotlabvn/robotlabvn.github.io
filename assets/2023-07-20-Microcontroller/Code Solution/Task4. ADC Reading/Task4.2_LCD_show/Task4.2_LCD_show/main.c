/*
 * Task4.2_LCD_Task.cpp
 * Author : KNIGHT
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd/lcd.h"

/*Hardware Configuration:
	PORT A = LCD (4bit mode)
	---------------------------------
	| PIN A1 = DB7 (LCD_DATA_PIN_3) |
	| PIN A2 = DB6 (LCD_DATA_PIN_2) |
	| PIN A3 = DB5 (LCD_DATA_PIN_1) |
	| PIN A4 = DB4 (LCD_DATA_PIN_0) |
	| PIN A5 = Enable		        |
	| PIN A6 = R/W		            |
	| PIN A7 = RS			        |
	---------------------------------
*/

// Global variable arrays for recording the AD value. Volatile, as required in the interrupt
volatile uint16_t analogArrayADC0[64];	

void program_lcd (void);
void propram_adc(void);
void program_adc_int(void);

int main(void)
{
    // Enable your program here
	program_adc();
}

void program_lcd(void)
{
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("Text on line 1");
	lcd_gotoxy(0,1);
	lcd_puts("line 2");
}
void program_adc(void)
{
	char Output[20];
	uint16_t ADC_Sum;
	float ADC_value;
	
	lcd_init(LCD_DISP_ON);
	
	DDRD &= ~ (1<<PIND0); // Pin D0 is input for the button.
	
	ADMUX |= (1 << MUX0)| (1 << MUX1); //set the ADC channel to 3
	ADMUX |=(1<<REFS0); // AVCC is reference voltage.
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1); //Prescaler as 64.
	ADCSRA |= (1<<ADEN); //ADC Enable
	ADCSRA |= (1<<ADSC); // ADC Single Conversion Start
	
	while(ADCSRA & (1<<ADSC)); // Wait for single conversion to finish
	ADC_Sum	=ADC; //// ADC is read out (discard first measurement, because inaccurate!)
	lcd_clrscr();
	lcd_puts("PD0:Measurement Start");
	
	while(1){
		//Wait for PD0 for Press
		if(!(PIND & (1<<PIND0))) 
		{
			//averaging
			ADC_Sum =0;
			for(uint8_t i=0; i<=3; i++){
				ADCSRA |= (1<<ADSC);
				while(ADCSRA & (1<<ADSC));
				ADC_Sum +=ADC;
			}
			ADC_Sum /= 4;
			ADC_value =0.0048828125*ADC_Sum;// Convert to floating point value, 5 volts / 1024 (10 bits) = 0.0048828125
			lcd_clrscr();
			lcd_puts("ADC Value:");
			dtostrf(ADC_value, 6, 4, Output);// dtostrf converts a floating-point number into ASCII
			lcd_puts(Output);
			_delay_ms(250);// Delay of keystroke and display
		}
	}
}
void program_adc_int(void)
{
	char Output[20];
	uint16_t ADC_Sum;
	float ADC_value;
	
	lcd_init(LCD_DISP_ON);
	
	
	ADMUX |= (1 << MUX0)| (1 << MUX1); //set the ADC channel to 3
	ADMUX |=(1<<REFS0); // AVCC is reference voltage.
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //Prescaler as 128.
	ADCSRA |= (1<<ADIE); //ADC Interrupt Enable
	ADCSRA |= (1<<ADEN); //ADC Enable
	  
	sei(); //Enable global Interrupts
	ADCSRA |= (1<<ADSC); // ADC Single Conversion Start
	
	
	while(1){
		for (int i=0; i<63; i++)
		{
			ADC_Sum +=analogArrayADC0[i];
		}
		ADC_value = 0.0000762939453125 * ADC_Sum; // 5 volts / 1024 (10 bits) / 64 (number of measurements) = 0.0000762939453125
		ADC_Sum =0;
		lcd_clrscr();
		lcd_puts("ADC_value:");
		dtostrf(ADC_value, 6, 4, Output);
		lcd_puts(Output);
		lcd_puts("(V)");
		_delay_ms(250);	
	}
}
ISR(ADC_vect){
	//Channel switching for AD Conversion
	uint16_t AD_val; // Auxiliary variable for recording the AD value. Direct handover of the ADC causes inaccuracies
	AD_val =ADC;
	for (int i=62; i>=0; i--){
		analogArrayADC0[i+1]=analogArrayADC0[i];
	}
	analogArrayADC0[0]= AD_val;
	ADMUX |= (1 << MUX0)| (1 << MUX1); //set the ADC channel to 3
	ADMUX |=(1<<REFS0); // AVCC is reference voltage.
	ADCSRA |= (1<<ADSC);	//ADC Single Conversion start
	
}