/*
 * Setpoint.c
 *
 *  Created on: 19.06.2021
 *      Author: MK
 */

#include "Setpoint.h"
#include "Config.h"
#include "Util.h"
#include "ADC_DMA.h"

static uint16_t raw_setpoint = 0;

void setpoint_init(void) {
	ADC_init(NBR_OF_CHANNELS);
	ADC_channel_config(SETPOINT_CHANNEL);
	DMA_init((uint32_t*)&raw_setpoint);
}

int16_t get_setpoint(void) {
	/* rescale raw measurement to physical setpoint value */
	int16_t setpoint;
	setpoint = scale(raw_setpoint, 0, ADC_RESOLUTION, -SETPOINT_LIMIT, SETPOINT_LIMIT);

	return setpoint;
}
