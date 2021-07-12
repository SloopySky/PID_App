/*
 * Scheduler.h
 *
 *  Created on: 29.06.2021
 *      Author: marek
 */

#ifndef APPLICATIONLAYER_SCHEDULER_H_
#define APPLICATIONLAYER_SCHEDULER_H_

#include <stdint.h>
#include <stdbool.h>

void scheduler_run(void);

bool scheduler_period_elapsed(void);

uint32_t get_scheduler_time_elapsed_ms(void);

#endif /* APPLICATIONLAYER_SCHEDULER_H_ */
