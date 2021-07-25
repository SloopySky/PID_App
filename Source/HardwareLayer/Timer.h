/*
 * PWM.h
 *
 *  Created on: 15.07.2021
 *      Author: MK
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"

void timer_init(uint16_t period_ms);
uint32_t get_current_time_ms(void);

#endif /*TIMER_H_ */
