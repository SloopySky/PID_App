/*
 * Diagnostics.h
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include <stdint.h>
#include <stdbool.h>

bool is_diagnostics_enabled(void);
void enable_diagnostics(void);
void disable_diagnostics(void);
bool diagnostics_period_elapsed(void);

#endif /* DIAGNOSTICS_H_ */
