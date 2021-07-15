/*
 * Motor.h
 *
 *  Created on: 09.06.2021
 *      Author: MK
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

#define FULL_SPEED 1000

typedef enum {CW, CCW} direction;

void motor_init(void);

void rotate_motor(int16_t speed);

#endif /* MOTOR_H_ */
