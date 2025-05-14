/*
 * control.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include "digital_filter.h"
#include "control.h"
#include "app_sm.h"
#include "main.h"
#include "hw.h"

extern ADC_HandleTypeDef hadc1;

uint32_t control_get_read_adc()
{
	return(HAL_ADC_GetValue(&hadc1));
}

float control_get_filtered_temp(digital_filter_t *f)
{
	uint32_t adc_reading = control_get_read_adc();
	digital_filter_put(f, adc_reading);

	float voltage = (OPERATIONAL_VOLTAGE / ADC_MAX_VALUE) * (float)digital_filter_get(f);
	float temperature = -101.099 * voltage + 347.473;

	return temperature;
}

uint16_t control_get_pid(float reference, float current_temp)
{
	static float error, error_1, error_2;
	static uint16_t control, control_1, control_2;

	const float a1 = -1, a2 = 0, b0 = -15, b1 = 20.235, b2 = -5.4482;

	error = reference - current_temp;

	control = (uint16_t)(-a1 * control_1 - a2 * control_2 + b0 * error + b1 * error_1 + b2 * error_2);

	if(control >= 1000)
		control = 1000;

	if(control <= 0)
		control = 0;

	error_2 = error_1;
	error_1 = error;
	control_2 = control_1;
	control_1 = control;

	return control;
}

