/*
 * global.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#include "main.h"
enum State st = START;
int counter1 = 0;
int counter2 = 0;
int timer_traffic = 0;
int time_RED = 6;
int time_GREEN = 3;
int time_YELLOW = 3;

void Update_led(){
	if (st == RED_MODIFY) blinks_in_LED(0);
	if (st == YELLOW_MODIFY) blinks_in_LED(1);
	if (st == GREEN_MODIFY) blinks_in_LED(2);
};

void display_digit(){
	display_in_Pair(counter1, counter2);
}

void fsm_traffic_light(){
	timer_traffic++;
	if (st== GREEN_RED||st== YELLOW_RED||st== RED_GREEN ||st== RED_YELLOW){
	  if (timer_traffic >= 100){
		  counter1--;
		  counter2--;
		  counter1 = (counter1 < 0) ? 0 : counter1;
		  counter2 = (counter2 < 0) ? 0 : counter2;
		  timer_traffic=0;
	  }

	}
	switch(st){
	case START:
		if (CheckButton(0)){
			st = GREEN_RED;
			counter1 = time_GREEN;
			counter2 = time_RED;
			timer_traffic = 0;
			GREEN_1(); RED_2();
		}
		break;

	case GREEN_RED:
		GREEN_1(); RED_2();
		if (counter1 <= 0){
			counter1 = time_YELLOW;
			YELLOW_1(); RED_2();
			st = YELLOW_RED;
		}
		if (CheckButton(0)){
			st = RED_MODIFY;
			TURN_OFF_ALL();
			counter1 = time_RED;
			counter2 = 2;
		}
		break;
	case YELLOW_RED:
		YELLOW_1(); RED_2();
		if (counter2 <= 0){
			st = RED_GREEN;
			counter1 = time_RED;
			counter2 = time_GREEN;
			timer_traffic = 0;
			RED_1(); GREEN_2();

		}
		if (CheckButton(0)){
			st = RED_MODIFY;
			TURN_OFF_ALL();
			counter1 = time_RED;
			counter2 = 2;
		}
		break;
	case RED_GREEN:
		RED_1(); GREEN_2();

		if (counter2 <= 0){
			st = RED_YELLOW;
			counter2 = time_YELLOW;
			RED_1(); YELLOW_2();

		}
		if (CheckButton(0)){
			st = RED_MODIFY;
			TURN_OFF_ALL();
			counter1 = time_RED;
			counter2 = 2;
		}
		break;
	case RED_YELLOW:
		RED_1(); YELLOW_2();

		if (counter2 <= 0){
			st = GREEN_RED;
			GREEN_1(); RED_2();
			counter1 = time_GREEN;
			counter2 = time_RED;
		}
		if (CheckButton(0)){
			st = RED_MODIFY;
			TURN_OFF_ALL();
			counter1 = time_RED;
			counter2 = 2;
		}
		break;


	case RED_MODIFY:
		if (timer_traffic >= 20) { // 500ms
			timer_traffic = 0;
			blinks_in_LED(0); // Nhấp nháy LED Đỏ
		}
		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton_1s(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton(2)){
			time_RED = counter1;
		}
		if (CheckButton(0)){
			st = YELLOW_MODIFY;
			counter1 = time_YELLOW;
			counter2 = 2;
			TURN_OFF_ALL();
			timer_traffic = 0;
		}
		break;
	case YELLOW_MODIFY:
		if (timer_traffic >= 20) {
			timer_traffic = 0;
			blinks_in_LED(1);
		}
		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton_1s(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton(2)){
			if (counter1 > time_RED) time_YELLOW = time_RED-1 ;
			else time_YELLOW = counter1;
			time_GREEN = time_RED - time_YELLOW;
		}
		if (CheckButton(0)){
			st = GREEN_MODIFY;
			counter1 = time_GREEN;
			counter2 = 3;
			TURN_OFF_ALL();
			timer_traffic = 0;
		}
		break;
	case GREEN_MODIFY:
		if (timer_traffic >= 20) {
			timer_traffic = 0;
			blinks_in_LED(2);
		}

		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton_1s(1)) {
			counter1++;
			if (counter1 >= 100) counter1=1;
		}
		if (CheckButton(2)){
			time_GREEN = counter1;
			if (time_GREEN >= time_RED) time_RED = time_GREEN + time_YELLOW;
			else time_YELLOW = time_RED - time_GREEN;
		}
		if (CheckButton(0)){
			st = START;
			TURN_OFF_ALL();
		}
		break;
	default:
	        st = GREEN_RED;
	        break;
	}



}
