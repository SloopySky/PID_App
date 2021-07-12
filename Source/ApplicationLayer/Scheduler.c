/*
 * Scheduler.c
 *
 *  Created on: 29.06.2021
 *      Author: marek
 */

#include "Scheduler.h"
#include "Util.h"
#include "Config.h"

static uint32_t previous_time_ms = 0;

void scheduler_run(void) {
	previous_time_ms = current_time_ms();
}

bool scheduler_period_elapsed(void) {
	return get_scheduler_time_elapsed_ms() >= SCHEDULER_PERIOD_MS;
}

uint32_t get_scheduler_time_elapsed_ms(void) {
	return current_time_ms() - previous_time_ms;
}
