/*
 * hw.h
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#ifndef HW_H_
#define HW_H_

void hw_load_turn_on_heat(void);
void hw_load_turn_off_heat(void);
void hw_fan_turn_on(void);
void hw_fun_turn_off(void);
void hw_fun_speed_control(uint16_t duty_cycle);
void hw_pwm_set_dc(uint16_t duty_cycle);
void hw_turn_on_tim_interrup(void);
void hw_turn_off_tim_interrup(void);

#endif /* HW_H_ */
