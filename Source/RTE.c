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


void get_state(void);
void send_state(void);

int main(void) {
	Hw_init();

	while(1) {
		get_state();
		rotate_motor(state.pid_output);

		if (is_diagnostics_enabled()) {
			if (diagnostics_period_elapsed()) {
				send_state();
			}
		}

		sleep_mode();
	}
}

void get_state(void) {
	state.current_time_s = miliseconds_to_seconds(current_time_ms());
	state.dt_ms = get_dt_ms();
	state.setpoint = get_setpoint();
	state.process_value = get_process_value();
	state.error = state.setpoint - state.process_value;
	state.pid_output = calc_pid_output(state.error, state.dt_ms);
}

void send_state(void) {

}
