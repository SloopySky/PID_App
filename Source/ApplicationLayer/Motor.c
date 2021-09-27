/*
 * Motor.c
 *
 *  Created on: 09.06.2021
 *      Author: MK
 */

#include "Motor.h"
#include "Config.h"
#include "DigitalOutput.h"
#include "PWM.h"

DigitalOutput motor_dir_pin = {
	MOTOR_PORT,		// uint32_t *port
	MOTOR_DIR_PIN	// uint32_t pin
};

static void set_direction(direction dir);
static void set_speed(uint16_t speed);

void motor_init(void) {
	digital_output_init(motor_dir_pin);

	PWM_init(MOTOR_PWM_TIMER);
	PWM_add_channel(MOTOR_PWM_CHANNEL, MOTOR_PORT);
}

void rotate_motor(int16_t speed) {
	if (speed < 0) {
		speed = FULL_SPEED - speed;
		set_direction(CCW);
	}
	else if (speed > 0){
		set_direction(CW);
	}
	set_speed(speed);
}

static void set_speed(uint16_t speed) {
	PWM_set_duty(MOTOR_PWM_CHANNEL, speed);
}

static void set_direction(direction dir) {
	if (dir == CW) {
		pin_set(motor_dir_pin);
	}
	else if (dir == CCW) {
		pin_reset(motor_dir_pin);
	}
	else {
		/* don't change the direction */
	}
}
