/*
 * contro.h
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#define ADC_MAX_VALUE ((1 << 12) - 1)
#define OPERATIONAL_VOLTAGE 3.3f

typedef struct control_pid_s
{
	uint8_t setpoint;

	float a1;
	float a2;
	float b0;
	float b1;
	float b2;
}control_pid_t;

uint32_t control_get_read_adc();

uint8_t control_get_filtered_temp();

uint16_t control_get_pid(control_pid_t pid, float reference, float current_temp);

#endif /* CONTRO_H_ */
