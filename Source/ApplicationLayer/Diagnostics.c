/*
 * Diagnostics.c
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#include "Diagnostics.h"
#include "UART.h"
#include "Timer.h"
#include "Config.h"

static bool diagnostics_enabled = false;

bool is_diagnostics_enabled(void) {
	return diagnostics_enabled;
}

void enable_diagnostics(void) {
	diagnostics_enabled = true;
}

void disable_diagnostics(void) {
	diagnostics_enabled = false;
}

bool diagnostics_period_elapsed(void) {
	static uint32_t time_ms = 0;

	bool elapsed = false;
	uint32_t current_time_ms = get_current_time_ms();
	if (current_time_ms - time_ms >= DIAGNOSTICS_PERIOD) {
		time_ms = current_time_ms;
		elapsed = true;
	}
	return elapsed;
}
