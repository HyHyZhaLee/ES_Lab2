/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#include "global.h"

#define MAX_TIMER 3
extern uint16_t flag_timer[MAX_TIMER];

void timer_init();
void timerBegin(uint16_t duration);
void setTimer(uint16_t duration, int ID);

#endif /* INC_SOFTWARE_TIMER_H_ */
