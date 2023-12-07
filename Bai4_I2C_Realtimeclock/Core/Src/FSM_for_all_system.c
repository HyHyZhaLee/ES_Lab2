/*
 * FSM_for_all_system.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Admin
 */


#include "FSM_for_all_system.h"

#define INIT	0
#define NORMAL_STATE	1
#define MOD_STATE	2
#define ALARM_STATE 3


uint8_t STATUS = INIT;

void fsm_for_input_processing(){
	if(isButtonE()){
		STATUS++;
		if(STATUS>ALARM_STATE) STATUS = INIT;
	}

	switch (STATUS) {
		case INIT:
			STATUS = NORMAL_STATE;
			break;
		case NORMAL_STATE:
			ds3231_ReadTime();
			displayTime();
		default:
			break;
	}
}
