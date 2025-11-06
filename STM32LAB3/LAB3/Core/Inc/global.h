/*
 * global.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nguye
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
extern int counter1;
extern int counter2;
extern int time_RED;
extern int time_GREEN;
extern int time_YELLOW;
enum State{ START, GREEN_RED, YELLOW_RED, RED_GREEN, RED_YELLOW , RED_MODIFY, GREEN_MODIFY, YELLOW_MODIFY,START_MODIFY  };
extern enum State st;
void fsm_normal();
void fsm_modify();
void control_by_hand();

#endif /* INC_GLOBAL_H_ */
