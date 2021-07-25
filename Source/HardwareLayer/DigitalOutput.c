/*
 * DigitalOutput.c
 *
 *  Created on: 19.06.2021
 *      Author: MK
 */

#include "DigitalOutput.h"
#include "stm32f1xx.h"

void digital_output_init(DigitalOutput output_pin) {
	GPIO_InitTypeDef gpio;

	gpio.Pin = output_pin.pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init((GPIO_TypeDef*)output_pin.port, &gpio);
}

void pin_set(DigitalOutput output_pin) {
	HAL_GPIO_WritePin((GPIO_TypeDef*) output_pin.port, output_pin.pin, GPIO_PIN_SET);
}

void pin_reset(DigitalOutput output_pin) {
	HAL_GPIO_WritePin((GPIO_TypeDef*) output_pin.port, output_pin.pin, GPIO_PIN_RESET);
}

