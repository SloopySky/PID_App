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


/*
systick_config(sample_time);

isr() {
	pid_control();

	if (diagnostics_enabled == true) {
		if (diagnostics_period_elapsed()) {
			send_state(state);
		}
	}

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
*/

/*
void pid_control(void) {
	state.current_time_s = 0,
	state.dt_ms = get_dt_ms();
	state.setpoint = 0;
	state.process_value = 0;
	state.error = get_setpoint() - get_process_value();
	state.pid_output = calc_pid_output(error, dt_ms);

	rotate_motor(pid_output);
}
*/


/*
OPCODE INTERRUPT

get_opcode();
response();
*/


int main(void) {
	Hw_init();

	while(1) {
	}
}
