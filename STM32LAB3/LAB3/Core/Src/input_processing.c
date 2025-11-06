/*
 * input_processing.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */


#include "main.h"
#include "software_timer.h"
enum ButtonState{ BUTTON_RELEASED , BUTTON_PRESSED , BUTTON_PRESSED_MORE_THAN_1_SECOND };
//enum ButtonState buttonState = BUTTON_RELEASED ;
int checkButton[3]={0,0,0};
int checkButton_1s[3]={0,0,0};
enum ButtonState buttonState[3]= {BUTTON_RELEASED,BUTTON_RELEASED,BUTTON_RELEASED};
//void process(){
//	HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
//}
int counter[3]={10,10,10};
void process1s(int idx){
	if (timer_flag[1] == 1){
		counter[idx]--;
		if (counter[idx] <= 0) {
			checkButton_1s[idx] = 1;
			counter[idx] = 10;
		}
		else checkButton_1s[idx] = 0;
		setTimer(1,10);
	}

}
void input_processing(int idx){
	switch (buttonState[idx]){
		case BUTTON_RELEASED:
			checkButton[idx] = 0;
			checkButton_1s[idx] = 0;
			if (is_button_pressed(idx)){
				buttonState[idx] = BUTTON_PRESSED;

				// INCREASE VALUE OF PORT A BY ONE UNIT
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(idx)){
				checkButton[idx] = 1;
				//TODO
				buttonState[idx] = BUTTON_RELEASED;
			}
			else {
				if (is_button_pressed_1s(idx)){
					buttonState[idx] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					checkButton_1s[idx] = 1;
				}
			}

			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			checkButton_1s[idx] = 0;
			checkButton[idx]=0;
			process1s(idx);
			if (!is_button_pressed(idx)){
				buttonState[idx] = BUTTON_RELEASED;
				counter[idx] = 10;
			}
			//TODO
			break;
		}
}
int CheckButton(int index){
	return checkButton[index];
}
int CheckButton_1s(int index){
	return checkButton_1s[index];
}
void fsm_for_input_processing(){
	for (int i=0; i<3; ++i) input_processing(i);
}
