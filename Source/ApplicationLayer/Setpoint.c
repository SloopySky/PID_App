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

int16_t get_setpoint(void) {
	/* get raw setpoint value from ADC */
	int16_t setpoint = get_adc(SETPOINT_CHANNEL);

	/* rescale raw measurement to physical setpoint value */
	setpoint = scale(setpoint, 0, ADC_RESOLUTION, -SETPOINT_LIMIT, SETPOINT_LIMIT);

	return setpoint;
}
