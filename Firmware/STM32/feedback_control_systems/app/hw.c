/*
 * hw.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */
#include <stdint.h>
#include "main.h"
#include "app_sm.h"
#include "hw.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

void hw_load_turn_on_heat(void)
{
	HAL_GPIO_WritePin(PWM_LOAD_GPIO_Port, PWM_LOAD_Pin, GPIO_PIN_SET);
}

void hw_load_turn_off_heat(void)
{
	HAL_GPIO_WritePin(PWM_LOAD_GPIO_Port, PWM_LOAD_Pin, GPIO_PIN_RESET);
}

void hw_fan_turn_on(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	hw_fan_speed_control(999);
}

void hw_fan_turn_off(void)
{
	hw_fan_speed_control(0);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

void hw_fan_speed_control(uint16_t duty_cycle)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	hw_pwm_set_dc(duty_cycle);
}

void hw_pwm_set_dc(uint16_t duty_cycle)
{
	uint16_t aux = duty_cycle;
	if(aux > 999)
		aux = 999;

	if(aux < 0)
		aux = 0.;

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, aux);
}

void hw_turn_on_tim_interrup(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void hw_turn_off_tim_interrup(void)
{
	HAL_TIM_Base_Stop_IT(&htim2);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		uart1_rx_cbk();
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		uart1_tx_cbk();
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
		tim3_cbk();
	}
}
