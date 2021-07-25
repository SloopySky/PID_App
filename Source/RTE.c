/**
  ******************************************************************************
  * @file    RTE.c
  * @author  MK
  * @version V1.0
  * @date    09.06.2021
  * @brief   RTE - RunTime Environment
  * main function that controls entire application
  ******************************************************************************
*/

#include "HwLayer.h"
#include "SwLayer.h"
#include "Config.h"
#include "Util.h"


/*
OPCODE INTERRUPT
get_opcode();
response();
*/

void PID_routine(void);
void send_state(void);

int main(void) {
	Hw_init();

	setpoint_init();
	motor_init();

	while(1) {
		PID_routine();

		if (is_diagnostics_enabled()) {}
		if (diagnostics_period_elapsed()) {
			send_state();
		}

		sleep_mode();
		/* Wakes up automatically when SAMPLE_TIME_MS expires */
	}
}

void PID_routine(void) {
	state.current_time_s = miliseconds_to_seconds(get_current_time_ms());
	state.setpoint = get_setpoint();
	state.process_value = 0;  // get_process_value();
	state.error = state.setpoint - state.process_value;
	state.pid_output = calc_pid_output(state.error, SAMPLE_TIME_MS);
	rotate_motor(state.pid_output);
}

void send_state(void) {
	printf("----------\n");
	printf("Time = %u [s]\n", state.current_time_s);
	printf("Setpoint = %d [deg]\n", state.setpoint);
	printf("Process value = %d [deg]\n", state.process_value);
	printf("Error = %d [deg]\n", state.error);
	printf("PID output = %d\n", state.pid_output);
}
