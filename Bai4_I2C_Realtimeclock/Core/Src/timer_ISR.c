/*
 * timer_ISR.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Admin
 */

#include "global.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timerRun();
		inputProcessing();
		// 1ms interrupt here
	}
}

