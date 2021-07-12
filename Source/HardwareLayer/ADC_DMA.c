/*
 * ADC_DMA.c
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#include "ADC_DMA.h"

static ADC_HandleTypeDef hadc1;
static DMA_HandleTypeDef hdma1;

static void channel_pin_config(uint32_t channel);


void ADC_init(uint8_t nbr_of_channels) {
	__HAL_RCC_ADC1_CLK_ENABLE();

	RCC_PeriphCLKInitTypeDef PeriphClkInit;
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

	hadc1.Instance = ADC1;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.NbrOfConversion = nbr_of_channels;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.NbrOfDiscConversion = 1;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	HAL_ADC_Init(&hadc1);
}

void ADC_channel_config(uint32_t channel) {
	ADC_ChannelConfTypeDef ch;
	ch.Channel = channel;
	ch.Rank = ADC_REGULAR_RANK_1;
	ch.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc1, &ch);

	channel_pin_config(channel);
}

static void channel_pin_config(uint32_t channel) {
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	/* ADC_CHANNEL_0 - ADC_CHANNEL_7 connected to GPIOA,
	 * to GPIO_PIN_0 - GPIO_PIN_7 correspondingly
	 * ADC_CHANNEL_8 - ADC_CHANNEL_9 connected to GPIOB,
	 * to GPIO_PIN_0 - GPIO_PIN_1 correspondingly */
	GPIO_TypeDef *port;
	if (channel <= ADC_CHANNEL_7) {
		port = GPIOA;
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if (channel <= ADC_CHANNEL_9) {
		port = GPIOB;
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/* for GPIOB index from 0 again */
		channel -= ADC_CHANNEL_8;
	}
	else {
		/* Channel not allowed.
		 * To not leave uninitialized,
		 * assign an unsupported address. */
		port = GPIOE;
	}

	if ((port == GPIOA) || (port == GPIOB)) {
		uint32_t pin[] = {GPIO_PIN_0,
						  GPIO_PIN_1,
						  GPIO_PIN_2,
						  GPIO_PIN_3,
						  GPIO_PIN_4,
						  GPIO_PIN_5,
						  GPIO_PIN_6,
						  GPIO_PIN_7};
		gpio.Pin = pin[channel];
		HAL_GPIO_Init(port, &gpio);
	}
}

void DMA_init(uint32_t * raw_value_addr) {
	__HAL_RCC_DMA1_CLK_ENABLE();

	hdma1.Instance = DMA1_Channel1;
	hdma1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma1.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma1.Init.MemInc = DMA_MINC_DISABLE;
	hdma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma1.Init.Mode = DMA_CIRCULAR;
	hdma1.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&hdma1);

	__HAL_LINKDMA(&hadc1, DMA_Handle, hdma1);

	uint8_t nbr_of_channels = hadc1.Init.NbrOfConversion;
	HAL_ADC_Start_DMA(&hadc1, raw_value_addr, nbr_of_channels);
}
