/*
 * State.h
 *
 *  Created on: 09.07.2021
 *      Author: MK
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>

typedef struct {
	uint16_t current_time_s;
	uint16_t dt_ms;
	int16_t setpoint;
	int16_t process_value;
	int16_t error;
	int16_t pid_output;
} State;

extern State state;

#endif /* STATE_H_ */
