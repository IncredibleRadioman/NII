/*
 * uart.c
 *
 *  Created on: 17 июн. 2018 г.
 *      Author: User
 */
#include "stm32l1xx.h"
void SEND_UART(USART_TypeDef* USARTx, char c) // отправить байт
{
while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)== RESET){}
USART_SendData(USARTx, c);
}

void SEND_UART_STR(USART_TypeDef* USARTx, char *s)
{
	uint8_t i=0;
	while(s[i]) {
		SEND_UART(USARTx, s[i]);
	i++;
	}
	SEND_UART(USARTx,'\r');
	SEND_UART(USARTx,'\n');
}

