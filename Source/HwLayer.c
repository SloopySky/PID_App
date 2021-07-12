/*
 * HwLayer.c
 *
 *  Created on: 10.07.2021
 *      Author: MK
 */

#include "HwLayer.h"
#include "stm32f1xx.h"
#include "Config.h"

void Hw_init(void) {
	SystemCoreClock = FREQ;	// FREQ defined in Config.h
	HAL_Init();

	UART_init(UART2, 115200);
}
