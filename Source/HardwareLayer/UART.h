/*
 * UART.h
 *
 *  Created on: 09.06.2021
 *      Author: marek
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f1xx.h"

typedef enum {UART1A, UART1B, UART2, UART3} uart_instance;

void UART_init(uart_instance instance_arg, uint32_t baudrate_arg);
void send_string(char * str);

#endif /* UART_H_ */
