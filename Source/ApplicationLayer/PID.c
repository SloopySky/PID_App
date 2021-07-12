/*
 * PID.c
 *
 *  Created on: 09.06.2021
 *      Author: marek
 */

#include "PID.h"
#include "Util.h"

#define ERROR_LIMIT		1000
#define INTEGRAL_LIMIT	5000
#define PID_LIMIT		1000

#define P_TUNE_LIMIT	1000
#define I_TUNE_LIMIT	1000
#define D_TUNE_LIMIT	1000


struct {
	uint16_t p;
	uint16_t i;
	uint16_t d;
} tune = {
	.p = 1,
	.i = 0,
	.d = 0
};


void set_tune(pid_term_t tune_term, uint16_t tune_value) {
	switch (tune_term) {
	case p:
		tune.p = limit(tune_value, 0, P_TUNE_LIMIT);
		break;
	case i:
		tune.i = limit(tune_value, 0, I_TUNE_LIMIT);
		break;
	case d:
		tune.d = limit(tune_value, 0, D_TUNE_LIMIT);
		break;
	}
}

uint16_t get_tune(pid_term_t tune_term) {
	uint16_t tune_value = 0;

	switch (tune_term) {
	case p:
		tune_value = tune.p;
		break;
	case i:
		tune_value = tune.i;
		break;
	case d:
		tune_value = tune.d;
		break;
	}

	return tune_value;
}

int32_t calc_pid_output(int16_t error, uint32_t sample_time_ms) {
	static int16_t previous_error = 0;
	static int16_t integral = 0;

	error = limit(error, -ERROR_LIMIT, ERROR_LIMIT);

	/* Proportional term calculation */
	int16_t proportional = error;

	/* Integral term calculation */
	integral += error * sample_time_ms / MILISECONDS_IN_SECOND ;
	integral = limit(integral, -INTEGRAL_LIMIT, INTEGRAL_LIMIT);

	/* Integral term calculation */
	int32_t derivative;
	if (sample_time_ms > 0) {
		derivative = (error - previous_error) * MILISECONDS_IN_SECOND / sample_time_ms;
	}
	else {
		derivative = 0;
	}
	previous_error = error;

	/* PID Equation */
	int32_t output = tune.p * proportional + tune.i * integral + tune.d * derivative;

	output = limit(output, -PID_LIMIT, PID_LIMIT);
	return output;
}


/*
void save_tunes_to_nvm(void);
void get_tunes_from_nvm(void);
*/
