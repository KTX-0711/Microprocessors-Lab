/*
 * software_timer.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#define NO_OF_TIMERS 3

int timer_counter[NO_OF_TIMERS];
int timer_flag[NO_OF_TIMERS];

void setTimer(int index, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
