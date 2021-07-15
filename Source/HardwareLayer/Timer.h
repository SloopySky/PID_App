/*
 * PWM.h
 *
 *  Created on: 15.07.2021
 *      Author: MK
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f1xx.h"

#define current_time_ms() HAL_GetTick()

void set_SysTick_counter_value(uint32_t cnt_value);
void set_SysTick_period(uint16_t period_ms);

#endif /*TIMER_H_ */
