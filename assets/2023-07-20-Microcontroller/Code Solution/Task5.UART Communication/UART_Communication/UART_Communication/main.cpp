/*
 * UART_Communication.cpp
 *
 * Created: 10/22/2018 8:29:41 AM
 * Author : KNIGHT
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


unsigned char message[35]="This is USART interrupt",count=0;


void usart_init(void);
void usart_tx(unsigned char msg);


int main(void)
{
	usart_init();
	
	usart_tx(message[count++]);              //increment count after transmission of first character
	
	while(1);
}


void usart_init()
{
	SREG|=0x80;                      //set global interrupt enable bit
	
	UBRR1=0x0c;                      //baud rate 4800, % error 0.2 %
	
	UCSR1B|=(1<<TXCIE1)|(1<<TXEN1)|(1<<RXEN1);   //enable transmitter, receiver, enable transmit complete interrupt
	
	UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);         //8-bit data, 1 stop bit, parity disabled, asynchronous operation
}


void usart_tx(unsigned char msg)
{
	while(!(UCSR1A & (1<<UDRE1)));               //wait until transmit buffer becomes empty
	
	UDR1=msg;                    //transmit first character by polling
}


ISR(USART1_TX_vect)
{
	if(count<35)
	{
		UDR1=message[count++];            //increment count after first transmission
	}
}