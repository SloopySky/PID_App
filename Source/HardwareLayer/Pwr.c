/*
 * PWM.c
 *
 *  Created on: 15.07.2021
 *      Author: MK
 */

#include "Pwr.h"
#include "stm32f1xx.h"

void Pwr_init(void) {
	__HAL_RCC_PWR_CLK_ENABLE();
}

void sleep_mode(void) {
	HAL_PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI);
}
