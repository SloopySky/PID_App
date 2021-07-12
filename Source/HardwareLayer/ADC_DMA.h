/*
 * ADC_DMA.h
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#ifndef ADC_DMA_H_
#define ADC_DMA_H_

#include "stm32f1xx.h"

#define ADC_RESOLUTION 0xFFF

/* ADC DMA initialization example:
 * ADC_init();
 * add_channel_config(ADC_CHANNEL_1);
 * DMA_init(&adc_value_addr);
*/

void ADC_init(uint8_t nbr_of_channels);
void ADC_channel_config(uint32_t channel);
void DMA_init(uint32_t* raw_value_addr);

#endif /* ADC_DMA_H_ */
