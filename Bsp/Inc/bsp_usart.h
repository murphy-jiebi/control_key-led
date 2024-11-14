#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "main.h"

typedef struct
{		
	uint8_t *pRxBuf;				
	uint16_t usRxBufSize;			
	__IO uint16_t usRxCount;	
	__IO uint8_t  usRxFrame;	
}UART_T;

extern UART_T usart1;
extern UART_T usart2;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

void DMA_Init(void);

void USART1_UART_Init(void);
void USART2_UART_Init(void);

void bsp_usartInit(void);

#endif

