/*
 * PWM.c
 *
 *  Created on: 15.07.2021
 *      Author: MK
 */

#include "Pwr.h"

#define MILISECONDS_IN_SECOND 1000

static uint32_t ms_to_ticks(uint16_t period_ms);

void set_SysTick_counter_value(uint32_t cnt_value) {
	SysTick->VAL += cnt_value - 1;
}

void set_SysTick_period(uint16_t period_ms) {
	uint32_t ticks = ms_to_ticks(period_ms);
	SysTick->LOAD = (uint32_t)(ticks - 1UL);
}

static uint32_t ms_to_ticks(uint16_t period_ms) {
	uint32_t ticks = (HAL_RCC_GetSysClockFreq() / MILISECONDS_IN_SECOND * period_ms);
	return ticks;
}
