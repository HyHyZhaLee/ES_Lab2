/*
 * button.h
 *
 *  Created on: Sep 25, 2023
 *      Author: HaHuyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "spi.h"
#include "gpio.h"
#include "global.h"

extern uint16_t button_count[16];

void button_init();
void button_Scan();
void inputProcessing();

uint8_t isButtonUp();
uint8_t isButtonDown();
uint8_t isButtonE();
#endif /* INC_BUTTON_H_ */

