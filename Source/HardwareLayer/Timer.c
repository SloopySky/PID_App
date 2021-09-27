/*
 * Timer.c
 *
 *  Created on: 15.07.2021
 *      Author: MK
 */

#include "Timer.h"
#include "stm32f1xx.h"

#define MILISECONDS_IN_SECOND 1000

static uint16_t timer_period_ms = 0;

void timer_init(uint16_t period_ms) {
	HAL_InitTick(TICK_INT_PRIORITY);
	SysTick_Config(SystemCoreClock / 1000 * period_ms);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0U);
	timer_period_ms = period_ms;
}

uint32_t get_current_time_ms(void) {
	return HAL_GetTick() * timer_period_ms;
}
