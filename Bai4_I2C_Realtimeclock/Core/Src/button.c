/*
 * button.c
 *
 *  Created on: Sep 25, 2023
 *      Author: HaHuyen
 */
#include "button.h"
#define LONG_PRESSED_DURATION 2000

uint16_t button_count[16];
uint16_t spi_button = 0x0000;
uint8_t flag_for_button[3];
int longPressedCounter[3];

void button_init(){
	HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
	for(int i = 0; i<3; i++){
		flag_for_button[i] = 0;
		longPressedCounter[i] = LONG_PRESSED_DURATION;
	}
}

void button_Scan(){
	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 0);
	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
	  HAL_SPI_Receive(&hspi1, (void*)&spi_button, 2, 10);
	  int button_index = 0;
	  uint16_t mask = 0x8000;
	  for(int i = 0; i < 16; i++){
		  if(i >= 0 && i <= 3){
			  button_index = i + 4; // do theo schematic thì spi gửi ko giống như button trên mạch
		  } else if (i >= 4 && i <= 7){  //-> cần convert lại cho nó đúng với thứ tự mình mún
			  button_index = 7 - i;
		  } else if (i >= 8 && i <= 11){
			  button_index = i + 4;
		  } else {
			  button_index = 23 - i;
		  }
		  if(spi_button & mask) button_count[button_index] = 0;
		  else button_count[button_index]++;
//		  if(spi_button & mask) button_count[i] = 0;
//		  else button_count[i]++;
		  mask = mask >> 1;
	  }
}

void inputProcessing(){
	if(button_count[3] >= 1){
		if(longPressedCounter[0] == LONG_PRESSED_DURATION){
			flag_for_button[0] = 1;
			longPressedCounter[0]--;
		}
		else {
			longPressedCounter[0]--;
			if(longPressedCounter[0]<=0) {
				longPressedCounter[0] = LONG_PRESSED_DURATION;
			}
		}
	}
	else longPressedCounter[0] = LONG_PRESSED_DURATION;


	if(button_count[7] >= 1){
		if(longPressedCounter[1] == LONG_PRESSED_DURATION){
			flag_for_button[1] = 1;
			longPressedCounter[1]--;
		}
		else {
			longPressedCounter[1]--;
			if(longPressedCounter[1]<=0) {
				longPressedCounter[1] = LONG_PRESSED_DURATION;
			}
		}
	}
	else longPressedCounter[1] = LONG_PRESSED_DURATION;

	if((button_count[12] >= 1)){
		if(longPressedCounter[2] == LONG_PRESSED_DURATION){
			flag_for_button[2] = 1;
			longPressedCounter[2]--;
		}
		else {
			longPressedCounter[2]--;
			if(longPressedCounter[2]<=0) {
				longPressedCounter[2] = LONG_PRESSED_DURATION;
			}
		}
	}
	else longPressedCounter[2] = LONG_PRESSED_DURATION;
}

uint8_t isButtonUp()
{
    if(flag_for_button[0]){
    	flag_for_button[0] = 0;
    	return 1;
    }
    else{
    	return 0;
    }
}
uint8_t isButtonDown()
{
    if(flag_for_button[1]){
    	flag_for_button[1] = 0;
    	return 1;
    }
    else{
    	return 0;
    }
}
uint8_t isButtonE()
{
    if(flag_for_button[2]){
    	flag_for_button[2] = 0;
    	return 1;
    }
    else{
    	return 0;
    }
}
