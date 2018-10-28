/*
 * uart.h
 *
 *  Created on: 17 θών. 2018 γ.
 *      Author: User
 */

#ifndef UART_H_
#define UART_H_


void SEND_UART(USART_TypeDef* USARTx, char c);
void SEND_UART_STR(USART_TypeDef* USARTx, char *s);
unsigned char GETCH_UART(USART_TypeDef* USARTx);
void READ_STR_UART(USART_TypeDef* USARTx,char* s);


#endif /* UART_H_ */
