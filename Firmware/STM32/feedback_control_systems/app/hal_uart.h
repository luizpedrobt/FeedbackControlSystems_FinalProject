/*
 * hal_uart.h
 *
 *  Created on: Jun 10, 2025
 *      Author: pedrobt
 */

#ifndef HAL_UART_H_
#define HAL_UART_H_

typedef enum hal_uart_baud_e
{
	BAUD_9600 = 0,
	BAUD_115200,
	BAUD_230400
}hal_uart_baud_t;

typedef enum hal_uart_parity_e
{
	PARITY_ODD = 0,
	PARITY_EVEN,
	PARITY_NONE
}hal_uart_parity_t;

typedef enum hal_uart_stop_bit_e
{
	STOP_BIT_NONE = 0,
	STOP_BIT_1,
	STOP_BIT_2
}hal_uart_stop_bit_t;

typedef enum hal_uart_config_status_e
{
	CONFIG_DONE = 0,
	CONFIG_ERROR
}hal_uart_config_status_t;

typedef struct hal_uart_configure_set_s
{
	hal_uart_baud_t baud_rate;
	hal_uart_parity_t parity;
	hal_uart_stop_bit_t stop_bits;
}hal_uart_configure_set_t;

void hal_uart1_init(void);
void hal_uart1_deinit(void);

void hal_uart1_configure(hal_uart_configure_set_t configure_set);

void hal_uart1_transmit_it(uint8_t *p_buf, uint8_t length);
void hal_uart1_receive_it(uint8_t *p_buf, uint8_t length);

#endif /* HAL_UART_H_ */
