/*
 * app.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "control.h"
#include "app_sm.h"
#include "main.h"
#include "hw.h"
#include "hal_uart.h"
#include "payload_composer.h"

#define MAX_OPERATIONAL_TEMP 75
#define AMBIENT_TEMP 25

extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart1;

sm_state_var_t st =
{
	.state = STATE_RESET,
	.pid =
	{
		.setpoint = 0,
		.a1 = -1.0f,
		.a2 = 0.0f,
		.b0 = -15.0f,
		.b1 = 20.235f,
		.b2 = -5.4482f
	}
};

sm_state_table_t sm_state_table[] =
{
	#define X(IDX, STATE, FUNC, NAME) FUNC,
		XMACRO_STATE_LIST
	#undef X
};

/* ----------------------------------- TRASNMIT PACKAGE ----------------------------------------- */

uint8_t tx_buffer[TX_BUFF_LENGTH] = {0};
uint8_t payload[5] = {0};

/* ----------------------------------- RECEIVE PACKAGE ------------------------------------------ */

uint8_t msg_raw[2] = {0};

/* ----------------------------------- PROCCESS VARIABLES --------------------------------------- */
uint8_t temperature = 0;
uint16_t duty_cycle_cmd = 0;
uint8_t fan_state = 0;
uint8_t heat_state = 0;
uint8_t peripheral_state = 0;

/* ----------------------------------- FLAG FOR TRANSMISSIONS ----------------------------------- */
bool transmit_flag = true;

void send_state_via_uart(sm_state_var_t state, uint8_t temperature, uint16_t control, uint8_t periph_st)
{
	if(transmit_flag)
	{
		transmit_flag = false;

		payload[0] = (uint8_t)state.state;
		payload[1] = temperature;
		payload[2] = control/10;
		payload[3] = state.pid.setpoint;
		payload[4] = periph_st;

		compose_data(payload, tx_buffer);

		hal_uart1_transmit_it(payload, TX_BUFF_LENGTH);
	}
}

void app_peripheral_init()
{
	HAL_ADC_Init(&hadc1);

	HAL_TIM_Base_Init(&htim1);
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Init(&htim3);

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);

	hal_uart1_init();
}

void unpack_frame(sm_state_var_t *state)
{
	uint8_t command = msg_raw[0];
	uint8_t sp = msg_raw[1];

	switch(command)
	{
		case 0:

			state->state = STATE_RESET;
			break;

		case 1:

			state->state = STATE_IDLE;
			break;

		case 2:

			state->state = STATE_HEAT;
			break;

		case 3:

			state->state = STATE_COOL;
			break;

		case 4:

			state->state = STATE_CONTROL;
			st.pid.setpoint = sp;
			break;

		default:

			st.state = st.state;

			break;
	}

}

void app_sm_init()
{
	app_peripheral_init();

	HAL_UART_Receive_IT(&huart1, msg_raw, 2);
}

void app_sm_run(sm_state_var_t *st)
{
	st->state = sm_state_table[st->state].func(st);
}

void app_run()
{
	app_sm_run(&st);
}

sm_state_t sm_reset_state(sm_state_var_t *st)
{
	sm_state_t next_state = STATE_IDLE;

	temperature = control_get_filtered_temp();

	return next_state;
}


sm_state_t sm_idle_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	st->pid.setpoint = 0;
	duty_cycle_cmd = 0;

	hw_load_turn_off_heat();
	hw_fan_turn_off();

	fan_state = 0;
	heat_state = 0;

	peripheral_state = (fan_state << 1) | heat_state;

	temperature = control_get_filtered_temp();

	return next_state;
}

sm_state_t sm_heat_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	st->pid.setpoint = 0;
	duty_cycle_cmd = 0;

	hw_load_turn_on_heat();
	hw_fan_turn_off();

	fan_state = 0;
	heat_state = 1;

	peripheral_state = (fan_state << 1) | heat_state;

	temperature = control_get_filtered_temp();

	if(temperature > MAX_OPERATIONAL_TEMP)
		 next_state = STATE_COOL;

	return next_state;
}

sm_state_t sm_cool_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	st->pid.setpoint = 0;
	duty_cycle_cmd = 1000;

	hw_fan_turn_on();
	hw_load_turn_off_heat();

	fan_state = 1;
	heat_state = 0;

	peripheral_state = (fan_state << 1) | heat_state;

	temperature = control_get_filtered_temp();

	if(temperature < AMBIENT_TEMP)
		next_state = STATE_IDLE;

	return next_state;
}

sm_state_t sm_control_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;

	duty_cycle_cmd = 0;

	if(st->pid.setpoint > MAX_OPERATIONAL_TEMP)
		st->pid.setpoint = MAX_OPERATIONAL_TEMP;

	if(st->pid.setpoint < AMBIENT_TEMP)
		st->pid.setpoint = AMBIENT_TEMP;

	hw_load_turn_on_heat();
	temperature = control_get_filtered_temp();

	duty_cycle_cmd = control_get_pid(st->pid, st->pid.setpoint, temperature);
	hw_fan_speed_control(duty_cycle_cmd);

	fan_state = 1;
	heat_state = 1;

	peripheral_state = (fan_state << 1) | heat_state;

	return next_state;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		unpack_frame(&st);
		HAL_UART_Receive_IT(&huart1, msg_raw, 2);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		transmit_flag = true;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if(htim == &htim2)
	{
		app_run();
	}

	if(htim == &htim3)
	{
		send_state_via_uart(st, temperature, duty_cycle_cmd, peripheral_state);
	}
}
