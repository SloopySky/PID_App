/*
 * Diagnostics.c
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#include "Diagnostics.h"
#include "Config.h"
#include "UART.h"

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
	static uint16_t sample_time_count = 0;
	sample_time_count += sample_time;

	bool elapsed = false;
	if (sample_time_count >= diagnostics_period) {
		elapsed = true;
		sample_time_count = 0;
	}
	return elapsed;
}
