/*
 * hal_uart.c
 *
 *  Created on: Jun 10, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include "hal_uart.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

void hal_uart1_init()
{
	HAL_UART_Init(&huart1);
}
void hal_uart1_deinit()
{
	HAL_UART_DeInit(&huart1);
}

void hal_uart1_configure_baud(hal_uart_baud_t baud_rate)
{
	switch(baud_rate)
	{
		case BAUD_9600:
			huart1.Init.BaudRate = 9600;

			break;

		case BAUD_115200:
			huart1.Init.BaudRate = 115200;

			break;

		case BAUD_230400:
			huart1.Init.BaudRate = 230400;

			break;

		default:
			huart1.Init.BaudRate = 9600;

			break;
	}
}

void hal_uart1_configure_parity(hal_uart_parity_t parity)
{
	switch(parity)
	{
		case PARITY_ODD:
			huart1.Init.Parity = UART_PARITY_ODD;

			break;

		case PARITY_EVEN:
			huart1.Init.Parity = UART_PARITY_EVEN;

			break;

		case PARITY_NONE:
			huart1.Init.Parity = UART_PARITY_NONE;

			break;

		default:
			huart1.Init.Parity = UART_PARITY_NONE;

			break;
	}
}

void hal_uart1_configure_stop_bits(hal_uart_stop_bit_t stop_bits)
{
	switch(stop_bits)
	{
		case STOP_BIT_1:
			huart1.Init.StopBits = UART_STOPBITS_1;

			break;

		case STOP_BIT_2:
			huart1.Init.StopBits = UART_STOPBITS_2;

			break;

		default:
			huart1.Init.StopBits = UART_STOPBITS_1;

			break;
	}
}

void hal_uart1_configure(hal_uart_configure_set_t configure_set)
{
	hal_uart1_deinit();

	hal_uart1_configure_baud(configure_set.baud_rate);
	hal_uart1_configure_parity(configure_set.parity);
	hal_uart1_configure_stop_bits(configure_set.stop_bits);

	hal_uart1_init();
}

void hal_uart1_transmit_it(uint8_t *p_buf, uint8_t length)
{
	HAL_UART_Transmit_IT(&huart1, p_buf, length);
}

void hal_uart1_receive_it(uint8_t *p_buf, uint8_t length)
{
	HAL_UART_Receive_IT(&huart1, p_buf, length);
}
