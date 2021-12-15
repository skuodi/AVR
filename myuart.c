/*
 * myuart.c
 *
 *  Created on: Dec 15, 2021
 *      Author: @skuodi
 */
#include "myuart.h"

/*
 *@brief This function initialises UART0 with 8N1 configuration
 */
void USART0_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
}

/*
 *@brief This function sends a single byte over UART0
 */
void USART0_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void sendDigits(long number){
	long tmp=number;					//duplicate the number
	int digits=0;						//will hold number of digits
	do{
		tmp/=10;
		digits++;
	}while(tmp);						//get the number of digits,
	uint8_t payload[digits];			//declare an array to hold them,
	for (int i = 0; i < digits; ++i)	//populate it in reverse order
	{
		payload[i]=number%10;
		number/=10;
	}
	for (int j = digits-1; j >= 0; --j)
	{
		USART0_Transmit(payload[j]+'0');//echo the digits in correct order
	}
}