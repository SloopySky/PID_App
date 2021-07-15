/*
 * Util.h
 *
 *  Created on: 19.06.2021
 *      Author: MK
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stm32f1xx.h"

#define MILISECONDS_IN_SECOND 1000

#define miliseconds_to_seconds(time_in_seconds) \
		((time_in_seconds) / MILISECONDS_IN_SECOND)

#define limit(x, min, max) \
		( (x) < (min) ? (min) : ((x) > (max) ? (max) : (x)) )

#define scale(x, in_min, in_max, out_min, out_max) \
		( ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min) )

#endif /* UTIL_H_ */
