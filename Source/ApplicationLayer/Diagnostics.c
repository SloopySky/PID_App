/*
 * Diagnostics.c
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#include "Diagnostics.h"

static bool diagnostics_enabled = false;

bool is_diagnostics_enabled(void) {
	return diagnostics_enabled;
}
