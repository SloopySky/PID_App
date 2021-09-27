/*
 * UART_DMA.c
 *
 *  Created on: 26.09.2021
 *      Author: MK
 */

#include "UART_DMA.h"
#include <stdbool.h>
#include <string.h>

#define UART_BAUDRATE_DEFAULT 115200

static UART_HandleTypeDef huart;
static DMA_HandleTypeDef hdma1_rx, hdma1_tx;

static void CLK_init(uart_instance instance);
static uint32_t UART_Tx_Pin(uart_instance instance);
static uint32_t UART_Rx_Pin(uart_instance instance);
static GPIO_TypeDef *UART_Port(uart_instance instance);
static USART_TypeDef *UART_Instance(uart_instance instance);
static uint32_t baudrate_bound(uint32_t baudrate_arg);
static void DMA_struct_defaults(DMA_HandleTypeDef *hdma);
static DMA_Channel_TypeDef *DMA_Rx_Channel(void);
static DMA_Channel_TypeDef *DMA_Tx_Channel(void);

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

void DMA_init(void) {
	__HAL_RCC_DMA1_CLK_ENABLE();

	hdma1_rx.Instance = DMA_Rx_Channel();
	DMA_struct_defaults(&hdma1_rx);
	HAL_DMA_Init(&hdma1_rx);
	__HAL_LINKDMA(&huart, hdmarx, hdma1_rx);

	hdma1_tx.Instance = DMA_Tx_Channel();
	DMA_struct_defaults(&hdma1_tx);
	HAL_DMA_Init(&hdma1_tx);
	__HAL_LINKDMA(&huart, hdmatx, hdma1_tx);
}

static void DMA_struct_defaults(DMA_HandleTypeDef *hdma) {
	hdma->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma->Init.PeriphInc = DMA_PINC_DISABLE;
	hdma->Init.MemInc = DMA_MINC_ENABLE;
	hdma->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma->Init.Mode = DMA_NORMAL;
	hdma->Init.Priority = DMA_PRIORITY_LOW;
}

static DMA_Channel_TypeDef *DMA_Rx_Channel(void) {
	DMA_Channel_TypeDef * rx_channel;

	if (huart.Instance == USART1) {
		rx_channel = DMA1_Channel5;
	}
	else if (huart.Instance == USART2) {
		rx_channel = DMA1_Channel6;
	}
	else if (huart.Instance == USART3) {
		rx_channel = DMA1_Channel3;
	}
	else {
		/* Incorrect UART initialization */
	}

	return rx_channel;
}

static DMA_Channel_TypeDef * DMA_Tx_Channel(void) {
	DMA_Channel_TypeDef * tx_channel;

	if (huart.Instance == USART1) {
		tx_channel = DMA1_Channel4;
	}
	else if (huart.Instance == USART2) {
		tx_channel = DMA1_Channel7;
	}
	else if (huart.Instance == USART3) {
		tx_channel = DMA1_Channel2;
	}
	else {
		/* Incorrect UART initialization */
	}

	return tx_channel;
}
