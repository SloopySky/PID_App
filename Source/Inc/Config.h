/*
 * Config.h
 *
 *  Created on: 10.06.2021
 *      Author: MK
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32f1xx.h"

/* CLOCK FREQUENCY */
/* Freq allowed range: [1Mhz; 8Mhz] with 1Mhz step */
/* Otherwise app will not work properly */
#define FREQ 					8000000

/* RTE SCHEDULER PERIOD [ms] */
#define SCHEDULER_PERIOD_MS 	1000

/* MIN SAMPLE TIME [ms] */
#define MIN_SAMPLE_TIME_MS 		5

/* UART CFG */
#define UART_INSTANCE 			UART1B  /* To choose from: {UART1A, UART1B, UART2, UART3} */
#define UART_BAUDRATE 			115200  /* To choose from: {9600, 19200, 38400, 115200} */

/* MOTOR CONFIG */
#define MOTOR_PORT				GPIOB
#define MOTOR_DIR_PIN			GPIO_PIN_5
#define MOTOR_PWM_TIMER			TIM3
#define MOTOR_PWM_CHANNEL		TIM_CHANNEL_1			

/* SETPOINT CONFIG */
#define NBR_OF_CHANNELS			1
#define SETPOINT_CHANNEL		ADC_CHANNEL_0
#define SETPOINT_LIMIT 			180

#endif /* CONFIG_H_ */

