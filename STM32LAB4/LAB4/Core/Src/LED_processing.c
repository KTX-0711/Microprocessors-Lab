/*
 * LED_processing.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */
#include "main.h"
#define NO_OF_LEDS 6
int led_buffer1[2]={0,0};
int led_buffer2[2]={0,0};

GPIO_TypeDef* LED_COLOR[NO_OF_LEDS] = {
    LED_RED1_GPIO_Port,
	LED_YELLOW1_GPIO_Port,
	LED_GREEN1_GPIO_Port,
    LED_RED2_GPIO_Port,
	LED_YELLOW2_GPIO_Port,
	LED_GREEN2_GPIO_Port
};

uint16_t LED_COLOR_Pin[NO_OF_LEDS] = {
    LED_RED1_Pin,
	LED_YELLOW1_Pin,
	LED_GREEN1_Pin,
    LED_RED2_Pin,
	LED_YELLOW2_Pin,
	LED_GREEN2_Pin
};
void display7SEG_Pair1(int num) {
    // Logic của hàm gốc là Common Anode (RESET = ON, SET = OFF)
    // Chúng ta giữ nguyên logic đó và chỉ thay đổi tên chân
    switch (num) {
        case 0: // a, b, c, d, e, f = ON; g = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET); // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);   // G1
            break;

        case 1: // b, c = ON; a, d, e, f, g = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);   // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, SET);   // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);   // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);   // G1
            break;

        case 2: // a, b, g, e, d = ON; c, f = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, SET);   // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET); // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);   // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 3: // a, b, g, c, d = ON; e, f = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);   // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 4: // f, g, b, c = ON; a, d, e = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);   // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, SET);   // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 5: // a, f, g, c, d = ON; b, e = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);   // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 6: // a, f, g, e, c, d = ON; b = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);   // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET); // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 7: // a, b, c = ON; d, e, f, g = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, SET);   // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);   // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);   // G1
            break;

        case 8: // a, b, c, d, e, f, g = ON
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET); // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        case 9: // a, b, c, d, f, g = ON; e = OFF
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET); // A1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET); // B1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET); // C1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET); // D1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);   // E1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET); // F1
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET); // G1
            break;

        default: // Tắt tất cả các segment
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
                                     GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, SET);
            break;
    }
}

void display7SEG_Pair2(int num) {

    switch (num) {
        case 0: // a, b, c, d, e, f = ON; g = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, RESET); // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);   // G2
            break;

        case 1: // b, c = ON; a, d, e, f, g = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, SET);    // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);   // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);   // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);   // G2
            break;

        case 2: // a, b, g, e, d = ON; c, f = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, SET);   // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, RESET); // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);   // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        case 3: // a, b, g, c, d = ON; e, f = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);   // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        case 4: // f, g, b, c = ON; a, d, e = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, SET);    // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);   // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        case 5: // a, f, g, c, d = ON; b, e = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, SET);    // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        case 6: // a, f, g, e, c, d = ON; b = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, SET);    // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, RESET); // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        case 7: // a, b, c = ON; d, e, f, g = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);   // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);   // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);   // G2
            break;

        case 8: // a, b, c, d, e, f, g = ON
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, RESET); // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2

//
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);  // A2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, RESET);   // E2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
//            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;


        case 9: // a, b, c, d, f, g = ON; e = OFF
            HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, RESET);  // A2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);  // B2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET); // C2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET); // D2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);   // E2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET); // F2
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET); // G2
            break;

        default: // Tắt tất cả các segment
            HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|
                                     GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, SET);
            HAL_GPIO_WritePin(A3_GPIO_Port,A3_Pin,SET );
            break;
    }
}

void scanLED1(int index){
	if (index >= 2){
		index = 0;
	}
	if (index == 0){
	  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	  display7SEG_Pair1(led_buffer1[0]);
	}
	else{
	  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
	  display7SEG_Pair1(led_buffer1[1]);
	}
}
void scanLED2(int index2){
	if (index2 >= 2){
		index2 = 0;
	}
	if (index2 == 0){
	  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
	  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
	  display7SEG_Pair2(led_buffer2[0]);
	}
	else{
	  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
	  display7SEG_Pair2(led_buffer2[1]);
	}
}
int index = 0;
void display_in_Pair(int num, int num2){

	led_buffer1[0] = num/10;
	led_buffer1[1] = num%10;
	led_buffer2[0] = num2/10;
	led_buffer2[1] = num2%10;
	scanLED1(index);
	scanLED2(index);
	index = !index;
}
void blinks_in_LED(int idx){
//		HAL_GPIO_WritePin(LED_COLOR[0], LED_COLOR_Pin[0], RESET);
//		HAL_GPIO_WritePin(LED_COLOR[1], LED_COLOR_Pin[1], RESET);
//		HAL_GPIO_WritePin(LED_COLOR[2], LED_COLOR_Pin[2], RESET);
		HAL_GPIO_TogglePin(LED_COLOR[idx], LED_COLOR_Pin[idx]);
		HAL_GPIO_TogglePin(LED_COLOR[idx+3], LED_COLOR_Pin[idx+3]);
}
void RED_1(){
	   HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
	   HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
}
void RED_2(){
	   HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
	   HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
}
void GREEN_1(){
	   HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
}
void GREEN_2(){
	   HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
}
void YELLOW_1(){
	   HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);
	   HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
}
void YELLOW_2(){
	   HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);
	   HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
}
void TURN_OFF_ALL(){
	   HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
	   HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);
	   HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
}
//void display_in_Pair2(int num){
//	led_buffer2[0] = num/10;
//	led_buffer2[1] = num%10;
//
//	if ( timer_flag[2] == 1){
//		scanLED2(index2);
//		index2=!index2;
//		setTimer(2, 50);
//	}
//}
