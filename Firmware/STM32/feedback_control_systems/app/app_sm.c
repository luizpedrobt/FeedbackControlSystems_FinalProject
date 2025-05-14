/*
 * app.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include "app_sm.h"
#include "digital_filter.h"
#include "control.h"
#include "main.h"
#include "hw.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;

static const char *sm_state_names[] =
{
	#define X(IDX, STATE, FUNC, NAME) NAME,
		XMACRO_STATE_LIST
	#undef X
};

sm_state_table_t sm_state_table[5] = {
	#define X(IDX, STATE, FUNC, NAME) FUNC,
		XMACRO_STATE_LIST
	#undef X
};

void app_peripheral_init()
{
	HAL_ADC_Init(&hadc1);
	HAL_TIM_Base_Init(&htim1);
	HAL_TIM_Base_Init(&htim2);
	HAL_UART_Init(&huart1);
}

void app_sm_init(sm_state_var_t *st)
{

}

void app_sm_run(sm_state_var_t *st)
{
	sm_state_t previous_state = st->state;
	st->state = sm_state_table[st->state].func(st);

	if(previous_state != st->state)
	{
		uint8_t msg[40] = {previous_state, st->state};
		uint8_t msg_size = 14 + 1 + 2 + 1;
		HAL_UART_Transmit(&huart1, msg, msg_size, 10000);
	}
}

sm_state_t sm_reset_state(sm_state_var_t *st)
{
	sm_state_t next_state = STATE_IDLE;

	return next_state;
}

sm_state_t sm_idle_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	uint8_t msg = 0;
	HAL_UART_Receive_IT(&huart1, &msg, 1);

	switch(msg)
	{
		case 0:
			next_state = STATE_HEAT;
			return next_state;

		case 1:
			next_state = STATE_COOL;
			return next_state;

		case 2:
			next_state = STATE_CONTROL;
			return next_state;

		case 3:
			next_state = STATE_IDLE;
			return next_state;

		default:
			next_state = STATE_IDLE;
			return next_state;
	}
}

sm_state_t sm_heat_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	hw_load_turn_on_heat();

	uint32_t past_time = HAL_GetTick();
	while((HAL_GetTick() - past_time) > 7000)
	{
		static uint8_t msg = 0;
		HAL_UART_Receive_IT(&huart1, &msg, 1);

		switch(msg)
		{
			case 0:
				next_state = STATE_HEAT;
				return next_state;

			case 1:
				next_state = STATE_COOL;
				return next_state;

			case 2:
				next_state = STATE_CONTROL;
				return next_state;

			case 3:
				next_state = STATE_IDLE;
				return next_state;

			default:
				next_state = STATE_IDLE;
				return next_state;
		}
	}
	next_state = STATE_IDLE;
	return next_state;
}

sm_state_t sm_cool_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state;
	hw_fan_turn_on();

	uint32_t past_time = HAL_GetTick();
	while((HAL_GetTick() - past_time) > 7000)
	{
		static uint8_t msg = 0;
		HAL_UART_Receive_IT(&huart1, &msg, 1);

		switch(msg)
		{
			case 0:
				next_state = STATE_HEAT;
				return next_state;

			case 1:
				next_state = STATE_COOL;
				return next_state;

			case 2:
				next_state = STATE_CONTROL;
				return next_state;

			case 3:
				next_state = STATE_IDLE;
				return next_state;

			default:
				next_state = STATE_IDLE;
				return next_state;
		}
	}
	next_state = STATE_IDLE;
	return next_state;
}

sm_state_t sm_control_state(sm_state_var_t *st)
{

}
