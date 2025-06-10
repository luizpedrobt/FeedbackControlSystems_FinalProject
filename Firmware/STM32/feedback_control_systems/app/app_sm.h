/*
 * app.h
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#ifndef APP_SM_H_
#define APP_SM_H_

#include "control.h"

#define XMACRO_STATE_LIST                                   \
		X(0, STATE_RESET,   sm_reset_state  , "RESET"  )    \
		X(1, STATE_IDLE,    sm_idle_state   , "IDLE"   )    \
		X(2, STATE_HEAT,    sm_heat_state   , "HEAT"   )    \
		X(3, STATE_COOL,    sm_cool_state   , "COOL"   )    \
		X(4, STATE_CONTROL, sm_control_state, "CONTROL")

typedef enum sm_state_e
{
	#define X(IDX, STATE, FUNC, NAME) STATE = IDX,
		XMACRO_STATE_LIST
	#undef X
}sm_state_t;

typedef struct sm_state_var_s
{
	sm_state_t state;
	control_pid_t pid;
}sm_state_var_t;

typedef sm_state_t (*sm_func_t)(sm_state_var_t *st);

typedef struct sm_state_table_s
{
	sm_func_t func;
}sm_state_table_t;

void app_run();
void app_peripheral_init();
void app_sm_init();
void app_sm_run(sm_state_var_t *st);

sm_state_t sm_reset_state(sm_state_var_t *st);
sm_state_t sm_idle_state(sm_state_var_t *st);
sm_state_t sm_heat_state(sm_state_var_t *st);
sm_state_t sm_cool_state(sm_state_var_t *st);
sm_state_t sm_control_state(sm_state_var_t *st);

#endif /* APP_H_ */
