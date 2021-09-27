/*
 * UART_DMA.h
 *
 *  Created on: 26.09.2021
 *      Author: MK
 */

#ifndef UART_DMA_H_
#define UART_DMA_H_

#include "stm32f1xx.h"

typedef enum {UART1A, UART1B, UART2, UART3} uart_instance;

void UART_init(uart_instance instance_arg, uint32_t baudrate_arg);
void DMA_init(void);

#endif /* UART_DMA_H_ */
