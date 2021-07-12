/*
 * UART.c
 *
 *  Created on: 09.06.2021
 *      Author: MK
 */

#include "UART.h"
#include <stdbool.h>
#include <string.h>

#define UART_BAUDRATE_DEFAULT 9600

/* UART HANDLER VARIABLE */
UART_HandleTypeDef huart;

/* STATIC FUNCTIONS PROTOTYPES */
static uint32_t baudrate_bound(uint32_t baudrate_arg);
static USART_TypeDef * UART_Instance(uart_instance instance);
static uint32_t UART_Tx_Pin(uart_instance instance);
static uint32_t UART_Rx_Pin(uart_instance instance);
static GPIO_TypeDef * UART_Port(uart_instance instance);
static IRQn_Type UART_IRQn(uart_instance instance);
static void CLK_init(uart_instance instance);

/*
#if ((UART_INSTANCE == UART1A) || (UART_INSTANCE == UART1B))
void USART1_IRQHandler(void) {
	HAL_TIM_IRQHandler(&huart);
}
#elif (UART_INSTANCE == UART2)
void USART2_IRQHandler(void) {
	HAL_TIM_IRQHandler(&huart);
}
#elif (UART_INSTANCE == UART3)
void USART3_IRQHandler(void) {
	HAL_TIM_IRQHandler(&huart);
}
#endif
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
	/* ... */
}

void UART_init(uart_instance instance_arg, uint32_t baudrate_arg) {
	/* RCC CLK ENABLE */
	CLK_init(instance_arg);

	/* Pins */
	GPIO_InitTypeDef gpio;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;

	/* UART Tx */
	gpio.Pin = UART_Tx_Pin(instance_arg);
	gpio.Mode = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(UART_Port(instance_arg), &gpio);

	/* UART Rx */
	gpio.Pin = UART_Rx_Pin(instance_arg);
	gpio.Mode = GPIO_MODE_AF_INPUT;
	HAL_GPIO_Init(UART_Port(instance_arg), &gpio);

	/* UART HANDLE */
	huart.Instance = UART_Instance(instance_arg);
	huart.Init.BaudRate = baudrate_bound(baudrate_arg);
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	huart.Init.Mode = UART_MODE_TX_RX;

	HAL_UART_Init(&huart);

	/* IRQ, NVIC */
	/*
	IRQn_Type irqn_instance = UART_IRQn(instance_arg);
	HAL_NVIC_SetPriority(irqn_instance, 0, 0);
	HAL_NVIC_EnableIRQ(irqn_instance);
	*/
}

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart, (uint8_t*)&ch, 1, 1000);
	return ch;
}

void send_string(char * str) {
	HAL_UART_Transmit(&huart, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}


static uint32_t baudrate_bound(uint32_t baudrate_arg) {
	/* UART baudrates to choose from: {9600, 19200, 38400, 115200} */
	uint32_t baudrate_allowed[] = {9600, 19200, 38400, 115200};
	uint8_t len = sizeof(baudrate_allowed)/sizeof(baudrate_allowed[0]);

	/* assume that baudrate_arg doesn't match any value of allowed baudrates */
	bool match = false;

	for (uint8_t i = 0; i < len; i++) {
		if (baudrate_arg == baudrate_allowed[i]) {
			/* baudrate_arg compliant - set is_compliant to true and break */
			match = true;
			break;
		}
		/* else baudrate_arg not compliant, don't change is_compliant state */
	}

	/* Return correct value of baudrate */
	if (match == false) {
		baudrate_arg = UART_BAUDRATE_DEFAULT;
	}
	/* else baudrate_arg value correct, don't change its value */

	return baudrate_arg;
}

static USART_TypeDef * UART_Instance(uart_instance instance) {
	USART_TypeDef * uart;

	switch (instance) {
	case UART1A:
	case UART1B:
		uart = USART1;
		break;
	case UART2:
		uart = USART2;
		break;
	case UART3:
		uart = USART3;
		break;
	}

	return uart;
}

static uint32_t UART_Tx_Pin(uart_instance instance) {
	uint32_t pin[] = {GPIO_PIN_9, GPIO_PIN_6, GPIO_PIN_2, GPIO_PIN_10};

	return pin[instance];
}

static uint32_t UART_Rx_Pin(uart_instance instance) {
	uint32_t pin[] = {GPIO_PIN_10, GPIO_PIN_7, GPIO_PIN_3, GPIO_PIN_11};

	return pin[instance];
}

static GPIO_TypeDef * UART_Port(uart_instance instance) {
	GPIO_TypeDef *port;

	switch (instance) {
	case UART1A:
	case UART2:
		port = GPIOA;
		break;
	case UART1B:
	case UART3:
		port = GPIOB;
		break;
	}

	return port;
}

static IRQn_Type UART_IRQn(uart_instance instance) {
	IRQn_Type irq_tbr; /* tbr - to be returned */

	switch (instance) {
	case UART1A:
	case UART1B:
		irq_tbr = USART1_IRQn;
		break;
	case UART2:
		irq_tbr = USART2_IRQn;
		break;
	case UART3:
		irq_tbr = USART3_IRQn;
		break;
	}

	return irq_tbr;
}


static void CLK_init(uart_instance instance) {
	switch (instance) {
	case UART1A:
		__HAL_RCC_USART1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case UART1B:
		__HAL_RCC_USART1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case UART2:
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case UART3:
		__HAL_RCC_USART3_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	}
}
