/*
 * LED_processing.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#ifndef INC_LED_PROCESSING_H_
#define INC_LED_PROCESSING_H_
#define NO_OF_LEDS 6

extern int led_buffer1[2];
extern int led_buffer2[2];
void display7SEG_Pair1(int num);
void display7SEG_Pair2(int num);
void scanLED1(int index);
void scanLED2(int index);
void display_in_Pair(int num, int num2);
void blinks_in_LED(int idx);
void TURN_OFF_ALL();
#endif /* INC_LED_PROCESSING_H_ */
