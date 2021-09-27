/**
  ******************************************************************************
  * @file    main.c
  * @author  MK
  * @version V1.0
  * @date    09.06.2021
  * @brief
  ******************************************************************************
*/

#include "stm32f1xx.h"
#include "Config.h"
#include "Util.h"

/* Include RTOS Libraries */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Include Hardware Layer Libraries */
#include "Timer.h"
#include "Pwr.h"

/* Include Software Layer Libraries */
#include "Diagnostics.h"
#include "Communication.h"
#include "Motor.h"
#include "PID.h"
#include "Setpoint.h"
#include "State.h"


/*
OPCODE INTERRUPT
get_opcode();
response();
*/

static void setup_hardware(void);
static void vTaskPID(void *pvParameters);
static void vTaskDiag(void *pvParameters);
static void PID_routine(void);
static void send_state(void);

int main(void) {
	setup_hardware();
	setpoint_init();
	motor_init();

	xTaskCreate(vTaskPID, "PID routine", 100, NULL, 1, NULL);
	xTaskCreate(vTaskDiag, "Diagnostics routine", 100, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1);
	return 0;
}

static void setup_hardware(void) {
	SystemCoreClock = FREQ;
	HAL_Init();

}

static void vTaskPID(void *pvParameters) {
	const TickType_t xDelay = SAMPLE_TIME_MS / portTICK_PERIOD_MS;
    for(;;) {
    	PID_routine();
		vTaskDelay(xDelay);
    }

	vTaskDelete(NULL);
}

static void vTaskDiag(void *pvParameters) {
	const TickType_t xDelay = DIAGNOSTICS_PERIOD_MS / portTICK_PERIOD_MS;
    for(;;) {
    	if (is_diagnostics_enabled()) {
    		send_state();
    	}
		vTaskDelay(xDelay);
    }

	vTaskDelete(NULL);
}

static void PID_routine(void) {
	state.current_time_s = miliseconds_to_seconds(get_current_time_ms());
	state.setpoint = get_setpoint();
	state.process_value = 0;  // get_process_value();
	state.error = state.setpoint - state.process_value;
	state.pid_output = calc_pid_output(state.error, SAMPLE_TIME_MS);
	rotate_motor(state.pid_output);
}

static void send_state(void) {
	/* IDs:
	 * 0x10 - timestamp
	 * 0x20 - setpoint
	 * 0x30 - process value
	 * 0x40 - error
	 * 0x50 - pid output
	 */
	send(0x10, state.current_time_s);
	send(0x20, state.setpoint);
	send(0x30, state.process_value);
	send(0x40, state.error);
	send(0x50, state.pid_output);
}
