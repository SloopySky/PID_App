/*
 * PWM.c
 *
 *  Created on: 07.07.2021
 *      Author: MK
 */

#include "PWM.h"
#include <stdbool.h>

#define MHz 1000000

TIM_HandleTypeDef htim;

static void CLK_init(TIM_TypeDef * tim_instance);
static void channel_pin_config(uint32_t channel, GPIO_TypeDef * port);
static uint16_t get_channel_pin(uint32_t channel, GPIO_TypeDef * port);


void PWM_init(TIM_TypeDef * tim_instance) {
	CLK_init(tim_instance);

	htim.Instance = tim_instance;
	htim.Init.Prescaler = HAL_RCC_GetSysClockFreq() / MHz - 1;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = PWM_PERIOD - 1;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.RepetitionCounter = 0;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(&htim);
}

static void CLK_init(TIM_TypeDef * tim_instance) {
	if (tim_instance == TIM1) {
		__HAL_RCC_TIM1_CLK_ENABLE();
	}
	else if (tim_instance == TIM2) {
		__HAL_RCC_TIM2_CLK_ENABLE();
	}
	else if (tim_instance == TIM3) {
		__HAL_RCC_TIM3_CLK_ENABLE();
	}
	else {
		/* Invalid timer instance */
	}
}

void PWM_add_channel(uint32_t channel, GPIO_TypeDef * port) {
	TIM_OC_InitTypeDef ch;
	ch.OCMode = TIM_OCMODE_PWM1;
	ch.Pulse = 0;
	ch.OCPolarity = TIM_OCPOLARITY_HIGH;
	ch.OCNPolarity = TIM_OCPOLARITY_LOW;
	ch.OCFastMode = TIM_OCFAST_ENABLE;
	ch.OCIdleState = TIM_OCIDLESTATE_SET;
	ch.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	channel_pin_config(channel, port);

	HAL_TIM_PWM_ConfigChannel(&htim, &ch, channel);
	HAL_TIM_PWM_Start(&htim, channel);
}

static void channel_pin_config(uint32_t channel, GPIO_TypeDef * port) {
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;

	if (htim.Instance == TIM1) {
		/* TIM1 Channels are available only on GPIOA */
		port = GPIOA;
	}
	else if (htim.Instance == TIM3) {
		if ((channel == TIM_CHANNEL_3) || (channel == TIM_CHANNEL_4)) {
			/* TIM3 Channels 3 and 4 are available only on GPIOB */
			port = GPIOB;
		}
	}
	gpio.Pin = get_channel_pin(channel, port);

	if (gpio.Pin != 0) {
		if (port == GPIOA) {
			__HAL_RCC_GPIOA_CLK_ENABLE();
		}
		else if (port == GPIOB) {
			__HAL_RCC_GPIOB_CLK_ENABLE();
		}
		HAL_GPIO_Init(port, &gpio);
	}
}

static uint16_t get_channel_pin(uint32_t channel, GPIO_TypeDef * port) {
	uint16_t pin = 0;
	bool is_channel_allowed = (channel == TIM_CHANNEL_1) ||
							  (channel == TIM_CHANNEL_2) ||
							  (channel == TIM_CHANNEL_3) ||
							  (channel == TIM_CHANNEL_4);

	if (is_channel_allowed == true) {
		if (htim.Instance == TIM1) {
			uint16_t pin_allowed[] = {GPIO_PIN_8,
									  GPIO_PIN_9,
									  GPIO_PIN_10,
									  GPIO_PIN_11};
			pin = pin_allowed[channel/4];
		}
		else if (htim.Instance == TIM2) {
			if (port == GPIOA) {
				uint16_t pin_allowed[] = {GPIO_PIN_15,
										  GPIO_PIN_1,
										  GPIO_PIN_2,
										  GPIO_PIN_3};
				pin = pin_allowed[channel/4];
			}
			else if (port == GPIOB) {
				uint16_t pin_allowed[] = {0,
										  GPIO_PIN_3,
										  GPIO_PIN_10,
										  GPIO_PIN_11};
				pin = pin_allowed[channel/4];
			}
		}
		else if (htim.Instance == TIM3) {
			if (port == GPIOA) {
				uint16_t pin_allowed[] = {GPIO_PIN_6,
										  GPIO_PIN_7,
										  0,
										  0};
				pin = pin_allowed[channel/4];
			}
			else if (port == GPIOB) {
				uint16_t pin_allowed[] = {GPIO_PIN_4,
										  GPIO_PIN_5,
										  GPIO_PIN_0,
										  GPIO_PIN_1};
				pin = pin_allowed[channel/4];
			}
		}
	}
	/* If pin value remains 0,
	 * it means that some wrong combination of arguments.
	 * Such value of the pin is not allowed and indicates an error.
	 */
	return pin;
}

void PWM_set_duty(uint32_t channel, uint16_t duty) {
	if (duty > PWM_PERIOD) {
		duty = PWM_PERIOD;
	}
	__HAL_TIM_SET_COMPARE(&htim, channel, duty);
}
