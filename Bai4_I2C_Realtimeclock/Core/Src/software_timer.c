/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE 1

//software timer variable
uint16_t flag_timer[MAX_TIMER];
uint16_t timer_counter[MAX_TIMER];
uint16_t timer_MUL[MAX_TIMER];


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer(uint16_t duration, int ID){
	timer_MUL[ID] = duration/TIMER_CYCLE;
	timer_counter[ID] = timer_MUL[ID];
	flag_timer[ID] = 0;
}

/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void timerRun(){
	for(int i = 0; i<MAX_TIMER;i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0) {
				flag_timer[i] = 1;
			}
		}
	}
}
void timerBegin(uint16_t duration){
	for(int i = 0; i<MAX_TIMER;i++) setTimer(duration, i);
}

