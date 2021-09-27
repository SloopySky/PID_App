/*
 * Communication.c
 *
 *  Created on: 10.06.2021
 *      Author: marek
 */

#include "UART_DMA.h"
#include "Config.h"

void communication_init(void) {
	UART_init(UART_INSTANCE, UART_BAUDRATE);
	DMA_init();
}

void send(uint8_t data_id, int32_t data) {
	// message sprintf
	// add to fifo
	// trigger uart_dma
}
