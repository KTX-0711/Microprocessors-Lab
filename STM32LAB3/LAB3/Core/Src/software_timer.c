/*
 * software_timer.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#include "software_timer.h"


void setTimer(int index, int duration){
	timer_counter[index] = duration;
	timer_flag[index] = 0;
}

void timerRun(){
	for (int i=0; i<NO_OF_TIMERS; ++i){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
