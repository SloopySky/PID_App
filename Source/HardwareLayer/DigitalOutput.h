/*
 * DigitalOutput.h
 *
 *  Created on: 19.06.2021
 *      Author: MK
 */

#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_

#include "stdint.h"

typedef struct {
	uint32_t *port;
	uint32_t pin;
} DigitalOutput;

void digital_output_init(DigitalOutput output_pin);
void pin_set(DigitalOutput output_pin);
void pin_reset(DigitalOutput output_pin);

#endif /* DIGITALOUTPUT_H_ */
