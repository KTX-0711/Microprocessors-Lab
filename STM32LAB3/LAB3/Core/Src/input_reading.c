/*
 * input_reading.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */


#include "main.h"

#define NO_OF_BUTTONS 3
#define NO_OF_LEDS 6
# define DURATION_FOR_AUTO_INCREASING 100
# define BUTTON_IS_PRESSED GPIO_PIN_RESET
# define BUTTON_IS_RELEASED GPIO_PIN_SET

GPIO_TypeDef* BUTTON_GPIO_Port[NO_OF_BUTTONS] = {
    BUTTON_1_GPIO_Port,
    BUTTON_2_GPIO_Port,
    BUTTON_3_GPIO_Port
};

uint16_t BUTTON_Pin[NO_OF_BUTTONS] = {
    BUTTON_1_Pin,
    BUTTON_2_Pin,
    BUTTON_3_Pin
};




static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer0[NO_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];



void button_reading ( void ){
	for ( char i = 0; i < NO_OF_BUTTONS ; i++){
		 debounceButtonBuffer0[i] = debounceButtonBuffer1[i];
		 debounceButtonBuffer1[i] = debounceButtonBuffer2[i];
		 debounceButtonBuffer2[i] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port[i] , BUTTON_Pin[i]);
		 if( (debounceButtonBuffer0[i] == debounceButtonBuffer1[i]) && (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) )
			 buttonBuffer[i] = debounceButtonBuffer2[i];
		 if( buttonBuffer[i] == BUTTON_IS_PRESSED ){
			 if( counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING ){
				 counterForButtonPress1s[i]++;
			 }
			 else{
				 flagForButtonPress1s[i] = 1;
			 }
		 }
		 else {
			 counterForButtonPress1s[i] = 0;
			 flagForButtonPress1s[i] = 0;
		 }
	}
}
unsigned char is_button_pressed(uint8_t index){
	if (index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
unsigned char is_button_pressed_1s(unsigned char index){
	if (index >= NO_OF_BUTTONS) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}
