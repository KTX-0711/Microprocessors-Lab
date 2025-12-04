/*
 * command_parser.c
 *
 *  Created on: Nov 28, 2025
 *      Author: nguye
 */
#include "command_parser.h"
#include "main.h"
#include <string.h>
#include "softwarre_timer.h"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

uint8_t command_flag = 0;
uint8_t command_data[30];
uint8_t command_index = 0;
uint8_t parser_status = 0;
uint8_t request = 0;
uint8_t done = 0;
uint32_t ADC_value = 0;

typedef enum {
	PARSER_IDLE,
	PARSER_READING
} ParserState;
ParserState st = PARSER_IDLE;

typedef enum{
	UART_IDLE, UART_READING, UART_WAIT
} UartState;

UartState st2 = UART_IDLE;
char str[30];

void command_parser_fsm(){

	uint8_t curr_index = (index_buffer == 0) ? (MAX_BUFFER_SIZE - 1) : (index_buffer - 1);
	uint8_t received_char = buffer[curr_index];

	switch(st){
		case PARSER_IDLE:
			if (received_char == '!') {
				st = PARSER_READING;
				command_index = 0;
			}
			break;
		case PARSER_READING:
			if (received_char == '#'){
				st = PARSER_IDLE;
				command_data[command_index] = '\0';

				if (strcmp((char*)command_data,"RST") == 0){
					command_flag = 1;
					request = 1;
				}
				else if (strcmp((char*)command_data,"OK") == 0){
					command_flag = 1;
					done = 1;
				}
			}
			else if (received_char == '!'){
				command_index = 0;
			}
			else {
				command_data[command_index++] = received_char;
				if (command_index >= 30) command_index = 0;
			}
			break;
		default :
			st = PARSER_IDLE;
			break;

	}

}


void uart_communication_fsm(){
	switch(st2){
		case UART_IDLE:
			if (request == 1){
				st2 = UART_READING;
				request = 0;
			}
			break;
		case UART_READING:
			HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			ADC_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "!ADC=%d#",(int) ADC_value), 1000);
			st2 = UART_WAIT;
			setTimer1(300);
			break;

		case UART_WAIT:
			if (done==1){
				st2 = UART_IDLE;
				done = 0;
			}
			if (timer1_flag == 1){
				st2 = UART_READING;
			}
	}
}
