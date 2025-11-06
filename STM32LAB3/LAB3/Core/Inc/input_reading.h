/*
 * input_reading.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

void fsm_for_input_processing ( void );
void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(unsigned char index);
#endif /* INC_INPUT_READING_H_ */
