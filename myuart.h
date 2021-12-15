/*
 * myuart.h
 *
 *  Created on: Dec 15, 2021
 *      Author: @skuodi
 */
#ifndef _MYUART_H
#define _MYUART_H 

#include <avr/io.h>
void USART0_Transmit(unsigned char data);
void USART0_Init(unsigned int ubrr);
void sendDigits(long number);

#endif