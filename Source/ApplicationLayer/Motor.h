/*
 * Motor.h
 *
 *  Created on: 09.06.2021
 *      Author: MK
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

void motor_init(uint32_t *port, uint32_t pin);

void rotate_motor(int16_t speed);

#endif /* MOTOR_H_ */
