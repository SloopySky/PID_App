/*
 * State.c
 *
 *  Created on: 09.07.2021
 *      Author: MK
 */

#include "State.h"

State state = {
	.current_time_s = 0,
	.dt_ms = 0,
	.setpoint = 0,
	.process_value = 0,
	.error = 0,
	.pid_output = 0
};
