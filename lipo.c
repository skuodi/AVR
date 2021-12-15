/*
 * lipo.c
 *
 *  Created on: Dec 15, 2021
 *      Author: @skuodi
 */
#define F_CPU 8000000UL
#define BAUD 9600
#define BRR (F_CPU/16/BAUD)-1

#include <avr/io.h>
#include <util/delay.h>
#include "myuart.h"
#include "lipo.h"

int main()
{
	USART0_Init(BRR);
	initAvcc();
	while(1){
		sendDigits(checkVcc());
		USART0_Transmit('\n');	//new line
		USART0_Transmit('\r');	//carriage return

		_delay_ms(1000);
	}
}

/*
 * @brief This function initialises the ADC with AVcc as reference and 1.1v internal as input
 */
void initAvcc(){
	ADMUX |= (1<<REFS0)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1);	//AVcc as reference; 1.1v as input
	ADCSRA |= (1<<ADEN | 1<<ADPS2 | 1<<ADPS1);			//enable ADC with prescaler 64
}

/*
 * @brief This function returns the value of Vcc in milivolts
 */
long checkVcc(){
	long reading,Vcc = 0;
	ADCSRA |= (1<<ADSC);								//start conversion
	while(ADCSRA&(1<<ADSC));							//wait for conversion to complete
	reading = (ADCH<<8)|(ADCL);							//acquire ADC results
	Vcc = 1125300L/reading;								//convert to millivolts
	return Vcc;
}
