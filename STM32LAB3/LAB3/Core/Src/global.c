/*
 * global.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#include "main.h"
#include "global.h"
#include "software_timer.h"
#include "input_reading.h"

void fsm_normal(){
	if (timer_flag[0] == 1 && (st== START ||st== GREEN_RED||st== YELLOW_RED||st== RED_GREEN ||st== RED_YELLOW)  ){
	  counter1--;
	  counter2--;
	  setTimer(0,100);
	}
	switch(st){
	case START:
		if (CheckButton(0)){
			st = GREEN_RED;
			counter1 = time_GREEN;
			counter2 = time_RED;
			GREEN_1(); RED_2();
		}

		//display_in_Pair(counter1,counter2);
		break;

	case GREEN_RED:

		GREEN_1(); RED_2();
		//display_in_Pair(counter1,counter2);
		if (counter1 <= 0){
			counter1 = time_YELLOW;
			YELLOW_1(); RED_2();
			st = YELLOW_RED;
		}
		if (CheckButton(0)){
			st = START_MODIFY;
			TURN_OFF_ALL();
		}
		break;
	case YELLOW_RED:
		YELLOW_1(); RED_2();
		//display_in_Pair(counter1,counter2);
		if (counter2 <= 0){
			counter1 = time_RED;
			counter2 = time_GREEN;
			RED_1(); GREEN_2();
			st = RED_GREEN;
		}
		break;
	case RED_GREEN:
		RED_1(); GREEN_2();
		//display_in_Pair(counter1,counter2);
		if (counter2 <= 0){
			counter2 = time_YELLOW;
			RED_1(); YELLOW_2();
			st = RED_YELLOW;
		}
		break;
	case RED_YELLOW:
		RED_1(); YELLOW_2();
		//display_in_Pair(counter1,counter2);
		if (counter2 <= 0){
			st = GREEN_RED;
			GREEN_1(); RED_2();
			counter1 = time_GREEN;
			counter2 = time_RED;
		}
		break;
	}
}

void fsm_modify(){

	switch (st){
	case START_MODIFY:
		counter1=0;
		counter2=0;
		if (CheckButton(0)){
			st = RED_MODIFY;
			counter1 = time_RED;
			counter2 = 1;
		}
		break;
	case RED_MODIFY:
		blinks_in_LED(0);
		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=0;
		}
		if (CheckButton_1s(1)) {
			counter1+=5;
			if (counter1 >= 100) counter1=0;
		}
		if (CheckButton(2)){
			time_RED = counter1;
		}
		if (CheckButton(0)){
			st = YELLOW_MODIFY;
			counter1 = time_YELLOW;
			counter2 = 2;
			TURN_OFF_ALL();
		}
		break;
	case YELLOW_MODIFY:
		blinks_in_LED(1);
		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=0;
		}
		if (CheckButton_1s(1)) {
			counter1+=5;
			if (counter1 >= 100) counter1=0;
		}
		if (CheckButton(2)){
			time_YELLOW = counter1;
			time_GREEN = time_RED - time_YELLOW;
		}
		if (CheckButton(0)){
			st = GREEN_MODIFY;
			counter1 = time_GREEN;
			counter2 = 3;
			TURN_OFF_ALL();
		}
		break;
	case GREEN_MODIFY:
		blinks_in_LED(2);
		if (CheckButton_1s(1)) {
			counter1+=5;
			if (counter1 >= 100) counter1=0;
		}
		if (CheckButton(1)) {
			counter1++;
			if (counter1 >= 100) counter1=0;
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
	}

}
