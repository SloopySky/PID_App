/*
 * Dt.c
 *
 *  Created on: 27.06.2021
 *      Author: MK
 */

#include "SleepMode.h"
#include "Timer.h"
#include "Pwr.h"

#define MS 1

void sleep_mode_init(void) {
	Pwr_init();
}

void sleep_mode(void) {
	set_SysTick_period(SLEEP_TIME_MS);
	enter_sleep_mode();
	set_SysTick_counter_value(SLEEP_TIME_MS);
	set_SysTick_period(MS);
}
