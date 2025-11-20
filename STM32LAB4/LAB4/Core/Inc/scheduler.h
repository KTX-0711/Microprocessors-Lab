/*
 * scheduler.h
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "main.h"

#define MAX_TASKS 20
#define TICK 10 // ms
/*	ERROR CODE: 1xy
 * 1: error
 * x: class <1: scheduler>
 * y: method
*/
#define ADD_TASK_ERROR 110
#define NOT_VALID_TASK_ID 111
#define SCH_MAX_TASKS 20
typedef struct TaskNode {
    void (*pTask)(void);
    struct TaskNode *next;
    uint32_t delay;
    uint32_t period;
    uint8_t runMe;
    uint32_t TaskID;
} TaskNode;

typedef struct {
    TaskNode *head;
    uint32_t nTasks;
} Tasks_t;

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;       // Delay ban đầu (để dùng cho task định kỳ)
    uint32_t Period;      // Chu kỳ lặp lại
    uint32_t RunMe;       // Cờ báo chạy (có thể bỏ nếu check trực tiếp)
    uint32_t TaskID;      // ID của task

    uint32_t NextRunTime;
} sTask;


void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (*pF)(void), uint32_t DELAY, const uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t TaskID);


#endif /* INC_SCHEDULER_H_ */
