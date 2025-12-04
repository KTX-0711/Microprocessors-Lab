/* scheduler.c */
#include "scheduler.h"
#include "main.h"

sTask SCH_tasks_G[MAX_TASKS];
uint32_t global_tick_count = 0;


#define TICK_OVERFLOW_THRESHOLD 1000000000

void SCH_Init(void) {
    unsigned char i;
    global_tick_count = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
}


void SCH_Update(void) {
    global_tick_count++;
    if (global_tick_count >= TICK_OVERFLOW_THRESHOLD) {

        global_tick_count -= TICK_OVERFLOW_THRESHOLD;

    }
}

uint32_t SCH_Add_Task(void (*pF)(void), uint32_t DELAY, uint32_t PERIOD) {
    unsigned char Index = 0;

    while ((SCH_tasks_G[Index].pTask != 0) && (Index < MAX_TASKS)) {
        Index++;
    }

    if (Index == MAX_TASKS) return MAX_TASKS; // Full

    SCH_tasks_G[Index].pTask = pF;
    SCH_tasks_G[Index].Delay = DELAY / 10;
    SCH_tasks_G[Index].Period = PERIOD / 10;
    SCH_tasks_G[Index].TaskID = Index;
    SCH_tasks_G[Index].RunMe = 0;

    if (global_tick_count + SCH_tasks_G[Index].Delay >= TICK_OVERFLOW_THRESHOLD) SCH_tasks_G[Index].NextRunTime = global_tick_count + SCH_tasks_G[Index].Delay - TICK_OVERFLOW_THRESHOLD;
    else SCH_tasks_G[Index].NextRunTime = global_tick_count + SCH_tasks_G[Index].Delay;

//    SCH_tasks_G[Index].NextRunTime = global_tick_count + SCH_tasks_G[Index].Delay;

    return Index;
}

void SCH_Dispatch_Tasks(void) {
    unsigned char Index;

    for (Index = 0; Index < MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].pTask) {
            if ((int32_t)(global_tick_count - SCH_tasks_G[Index].NextRunTime) >= 0) {
                (*SCH_tasks_G[Index].pTask)();

                if (SCH_tasks_G[Index].Period == 0) {
                    SCH_Delete_Task(Index);
                } else {
                    SCH_tasks_G[Index].NextRunTime += SCH_tasks_G[Index].Period;
                }
            }
        }
    }
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    if (taskID >= MAX_TASKS) return 0;

    SCH_tasks_G[taskID].pTask = 0x0000;
    SCH_tasks_G[taskID].Delay = 0;
    SCH_tasks_G[taskID].Period = 0;
    SCH_tasks_G[taskID].RunMe = 0;
    SCH_tasks_G[taskID].NextRunTime = 0;

    return 1;
}
