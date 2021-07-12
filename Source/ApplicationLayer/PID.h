/*
 * PID.h
 *
 *  Created on: 09.06.2021
 *      Author: marek
 */

#ifndef PID_H_
#define PID_H_

#include <stdint.h>

typedef enum {p, i, d} pid_term_t;

void set_tune(pid_term_t tune_term, uint16_t tune_value);

uint16_t get_tune(pid_term_t tune_term);

int32_t calc_pid_output(int16_t error, uint32_t sample_time_ms);

#endif /* PID_H_ */
