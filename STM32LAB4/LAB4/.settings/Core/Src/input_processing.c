/*
 * input_processing.c
 *
 * Tối ưu: Kích hoạt sự kiện ngay khi nhấn (Falling Edge) thay vì chờ nhả.
 */

#include "main.h"

enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };

static enum ButtonState buttonState[NO_OF_BUTTONS] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
static int checkButton[NO_OF_BUTTONS] = {0};      // Cờ nhấn dứt khoát
static int checkButton_1s[NO_OF_BUTTONS] = {0};   // Cờ nhấn giữ

static int counter_for_long_press[NO_OF_BUTTONS] = {0};

#define TIME_FOR_LONG_PRESS  50  // 100 * 10ms = 1s (Thời gian chờ để bắt đầu auto-repeat)
#define TIME_FOR_AUTO_REPEAT 20   // 20 * 10ms = 200ms (Tốc độ nhảy số khi giữ nút - nên để nhanh hơn 1s)

void input_processing(int idx){
    switch (buttonState[idx]){
        case BUTTON_RELEASED:
            if (is_button_pressed(idx)){
                buttonState[idx] = BUTTON_PRESSED;
                checkButton[idx] = 1;
                counter_for_long_press[idx] = TIME_FOR_LONG_PRESS;
            }
            break;

        case BUTTON_PRESSED:
            if (!is_button_pressed(idx)){
                buttonState[idx] = BUTTON_RELEASED;
            }
            else {
                counter_for_long_press[idx]--;
                if (counter_for_long_press[idx] <= 0){
                    buttonState[idx] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                    checkButton_1s[idx] = 1;
                    counter_for_long_press[idx] = TIME_FOR_AUTO_REPEAT;
                }
            }
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_pressed(idx)){
                buttonState[idx] = BUTTON_RELEASED;
            }
            else {
                counter_for_long_press[idx]--;

                if (counter_for_long_press[idx] <= 0){

                    checkButton_1s[idx] = 1;
                    counter_for_long_press[idx] = TIME_FOR_AUTO_REPEAT;
                }
            }
            break;
    }
}

int CheckButton(int index){
	if (index >= NO_OF_BUTTONS) return 0;
	if (checkButton[index] == 1){
		checkButton[index] = 0;
		return 1;
	}
	return 0;
}

int CheckButton_1s(int index){
	if (index >= NO_OF_BUTTONS) return 0;
	if (checkButton_1s[index] == 1){
		checkButton_1s[index] = 0;
		return 1;
	}
	return 0;
}

void fsm_for_input_processing(){
	for (int i=0; i < NO_OF_BUTTONS; ++i) input_processing(i);
}
