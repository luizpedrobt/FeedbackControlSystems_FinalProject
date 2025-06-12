/*
 * control.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include "control.h"
#include "main.h"

extern ADC_HandleTypeDef hadc1;

float error, error_1, error_2;
float control, control_1, control_2;

uint32_t control_get_read_adc(void)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint32_t adc_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	return(adc_raw);
}

uint8_t control_get_filtered_temp(void)
{
	uint32_t adc_reading = control_get_read_adc();

	float voltage = (OPERATIONAL_VOLTAGE / ADC_MAX_VALUE) * adc_reading;
	uint8_t temperature = (uint8_t)(-101.099 * voltage + 347.473);

	return temperature;
}

uint16_t control_get_pid(control_pid_t pid, float reference, float current_temp)
{
	error = reference - current_temp;

	control = (uint16_t)(-pid.a1 * control_1 - pid.a2 * control_2 + pid.b0 * error + pid.b1 * error_1 + pid.b2 * error_2);

	if(control >= 999)
		control = 999;

	if(control <= 0)
		control = 0;

	error_2 = error_1;
	error_1 = error;
	control_2 = control_1;
	control_1 = control;

	return control;
}

