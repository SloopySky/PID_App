/*
 * Dt.c
 *
 *  Created on: 27.06.2021
 *      Author: MK
 */

#include "Dt.h"
#include "Timer.h"

static uint32_t previous_time_ms = 0;

uint16_t get_dt_ms(void) {
	return current_time_ms() - previous_time_ms;
}

void dt_count_start(void) {
	previous_time_ms = current_time_ms();
}
