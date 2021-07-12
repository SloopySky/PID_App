/*
 * PWM.h
 *
 *  Created on: 07.07.2021
 *      Author: MK
 */

#ifndef HARDWARELAYER_PWM_H_
#define HARDWARELAYER_PWM_H_

#include "stm32f1xx.h"

#define PWM_PERIOD 1000

void PWM_init(TIM_TypeDef * tim_instance);

void PWM_add_channel(uint32_t channel, GPIO_TypeDef * port);

void PWM_set_duty(uint32_t channel, uint16_t duty);

#endif /* HARDWARELAYER_PWM_H_ */
