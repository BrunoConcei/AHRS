#ifndef _UART_H_
#define _UART_H_

#include <stdio.h>

void USART_Config(void); //��������
void USART_IT_Config(void);
int fputc(int ch, FILE *f);    //fputc�ض���
int fgetc(FILE *f); //fgetc�ض���

//------------RTOS layer-------------------
void vUARTIsrHandler(void * pvParameters);
#endif
