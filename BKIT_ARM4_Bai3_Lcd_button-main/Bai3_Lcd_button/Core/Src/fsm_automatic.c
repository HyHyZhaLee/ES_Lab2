/*
 * fsm_automatic.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Admin
 */


#include "fsm_automatic.h"
#define INIT            0
#define RED_GREEN       1
#define RED_YELLOW     	2
#define GREEN_RED     	3
#define YELLOW_RED		4

#define INPUT_AUTO		5
#define INPUT_RED		6
#define INPUT_YELLOW	7
#define INPUT_GREEN		8

#define RED_DURATION    7
#define YELLOW_DURATION 4
#define GREEN_DURATION  2

int INPUT_STATUS = INIT;
int AUTO_STATUS = INIT;

int red_duration = RED_DURATION;
int yellow_duration = YELLOW_DURATION;
int green_duration = GREEN_DURATION;

int temp_red_duration = RED_DURATION;
int temp_yellow_duration = YELLOW_DURATION;
int temp_green_duration = GREEN_DURATION;

int counter;

void fsm_for_input_processing(){
	if(button_count[0] == 1){
		INPUT_STATUS++;
		if(INPUT_STATUS>INPUT_GREEN) INPUT_STATUS = INPUT_AUTO;
		temp_red_duration = red_duration;
		temp_yellow_duration = yellow_duration;
		temp_green_duration = green_duration;
	}
	if(button_count[2] == 1){
		INPUT_STATUS++;
		if(INPUT_STATUS>INPUT_GREEN) INPUT_STATUS = INPUT_AUTO;
		red_duration = temp_red_duration;
		yellow_duration = temp_yellow_duration;
		green_duration = temp_green_duration;
	}
	switch(INPUT_STATUS){
		case INIT:
			INPUT_STATUS = INPUT_AUTO;
			break;
		case INPUT_AUTO:
			fsm_automatic_run();
			break;
		case INPUT_RED:
			toggleLED(RED);
			if(button_count[1] == 1) temp_red_duration++;
			break;
		case INPUT_YELLOW:
			toggleLED(YELLOW);
			if(button_count[1] == 1) temp_yellow_duration++;
			break;
		case INPUT_GREEN:
			toggleLED(GREEN);
			if(button_count[1] == 1) temp_green_duration++;
			break;
	}

}
void fsm_automatic_run() {
    switch (AUTO_STATUS) {
        case INIT:
        	setTimer(1000, 0);
        	AUTO_STATUS = RED_GREEN;
        	counter = green_duration;
        	displayTraffic(RED, GREEN);
        	break;
        case RED_GREEN:
        	if(counter<0){
        		AUTO_STATUS = RED_YELLOW;
        		counter = yellow_duration;
            	displayTraffic(RED, YELLOW);
        	}
        	break;
        case RED_YELLOW:
			if(counter<0){
				AUTO_STATUS = GREEN_RED;
				counter = green_duration;
            	displayTraffic(GREEN, RED);
			}
			break;
        case GREEN_RED:
			if(counter<0){
				AUTO_STATUS = YELLOW_RED;
				counter = yellow_duration;
				displayTraffic(YELLOW, RED);
			}
			break;
        case YELLOW_RED:
			if(counter<0){
				AUTO_STATUS = RED_GREEN;
				counter = green_duration;
				displayTraffic(RED, GREEN);
			}
			break;

    }
    if(flag_timer[0]){
    	setTimer(1000,0);
    	counter--;
    }
}




void displayTraffic(int led1, int led2) {
	lcd_Clear(WHITE);
    lcd_Fill(0, 0, 240, 20, BLUE);
    lcd_StrCenter(0, 2, "BKHCM_LAB3", WHITE, BLUE, 16, 1);
    lcd_ShowPicture(80, 115, 90, 90, gImage_logo);

    // Horizontal (led1)
    lcd_DrawCircle(88, 85, RED, 15, 0);
    lcd_DrawCircle(152, 85, GREEN, 15, 0);
    lcd_DrawCircle(120, 85, YELLOW, 15, 0);

    lcd_DrawCircle(88, 235, RED, 15, 0);
    lcd_DrawCircle(152, 235, GREEN, 15, 0);
    lcd_DrawCircle(120, 235, YELLOW, 15, 0);

    // Vertical (led2)
    lcd_DrawCircle(44, 128, RED, 15, 0);
    lcd_DrawCircle(44, 160, YELLOW, 15, 0);
    lcd_DrawCircle(44, 192, GREEN, 15, 0);

    lcd_DrawCircle(196, 128, RED, 15, 0);
    lcd_DrawCircle(196, 160, YELLOW, 15, 0);
    lcd_DrawCircle(196, 192, GREEN, 15, 0);

    if (led1 == RED) {
        lcd_DrawCircle(88, 85, RED, 15, 1);
        lcd_DrawCircle(88, 235, RED, 15, 1);
    } else if (led1 == YELLOW) {
        lcd_DrawCircle(120, 85, YELLOW, 15, 1);
        lcd_DrawCircle(120, 235, YELLOW, 15, 1);
    } else if (led1 == GREEN) {
        lcd_DrawCircle(152, 85, GREEN, 15, 1);
        lcd_DrawCircle(152, 235, GREEN, 15, 1);
    }

    // Check led2 and update the circles accordingly
    if (led2 == RED) {
        lcd_DrawCircle(44, 128, RED, 15, 1);
        lcd_DrawCircle(196, 128, RED, 15, 1);
    } else if (led2 == YELLOW) {
        lcd_DrawCircle(44, 160, YELLOW, 15, 1);
        lcd_DrawCircle(196, 160, YELLOW, 15, 1);
    } else if (led2 == GREEN) {
        lcd_DrawCircle(44, 192, GREEN, 15, 1);
        lcd_DrawCircle(196, 192, GREEN, 15, 1);
    }
}
int toggle_state = 0, toggle_check = 0;
void toggleLED(int led){
	if(flag_timer[1]){
		setTimer(1000,1);
		toggle_state = 1-toggle_state;
		toggle_check = 0;
	}
	if(toggle_check) return;
	if(toggle_state){
		if(led == RED) displayTraffic(RED, RED);
		else if(led == YELLOW) displayTraffic(YELLOW, YELLOW);
		else if(led == GREEN) displayTraffic(GREEN, GREEN);
		toggle_check = 1;
		return;
	}
	lcd_Clear(WHITE);
    lcd_Fill(0, 0, 240, 20, BLUE);
    lcd_StrCenter(0, 2, "BKHCM_LAB3", WHITE, BLUE, 16, 1);
    lcd_ShowPicture(80, 115, 90, 90, gImage_logo);

    // Horizontal (led1)
    lcd_DrawCircle(88, 85, RED, 15, 0);
    lcd_DrawCircle(152, 85, GREEN, 15, 0);
    lcd_DrawCircle(120, 85, YELLOW, 15, 0);

    lcd_DrawCircle(88, 235, RED, 15, 0);
    lcd_DrawCircle(152, 235, GREEN, 15, 0);
    lcd_DrawCircle(120, 235, YELLOW, 15, 0);

    // Vertical (led2)
    lcd_DrawCircle(44, 128, RED, 15, 0);
    lcd_DrawCircle(44, 160, YELLOW, 15, 0);
    lcd_DrawCircle(44, 192, GREEN, 15, 0);

    lcd_DrawCircle(196, 128, RED, 15, 0);
    lcd_DrawCircle(196, 160, YELLOW, 15, 0);
    lcd_DrawCircle(196, 192, GREEN, 15, 0);
    toggle_check = 1;
}
