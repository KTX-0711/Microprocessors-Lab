/* scheduler.c */
#include "scheduler.h"
#include "main.h"

sTask SCH_tasks_G[MAX_TASKS];
uint32_t global_tick_count = 0;

// Định nghĩa ngưỡng tràn số (Ví dụ 1 tỷ)
#define TICK_OVERFLOW_THRESHOLD 1000000000

void SCH_Init(void) {
    unsigned char i;
    global_tick_count = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
}

// --- HÀM UPDATE: XỬ LÝ ĐỒNG BỘ KHI TRÀN SỐ ---
void SCH_Update(void) {
    global_tick_count++;

    // Nếu chạm ngưỡng 1 tỷ
    if (global_tick_count >= TICK_OVERFLOW_THRESHOLD) {

        // 1. Reset biến đếm toàn cục
        global_tick_count -= TICK_OVERFLOW_THRESHOLD;

        // 2. Đồng bộ lại thời gian mục tiêu của TẤT CẢ các task
        // Để đảm bảo tính tương đối của thời gian không bị sai lệch
        for (int i = 0; i < MAX_TASKS; i++) {
            if (SCH_tasks_G[i].pTask) { // Nếu task đang tồn tại
                // Trừ NextRunTime đi 1 lượng tương ứng
                SCH_tasks_G[i].NextRunTime -= TICK_OVERFLOW_THRESHOLD;
            }
        }
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

    // Tính NextRunTime bình thường.
    // Lưu ý: Nếu global + Delay vượt quá 4 tỷ (uint32) thì mới lo,
    // còn vượt quá 1 tỷ thì kệ nó, hàm SCH_Update sẽ tự xử lý khi global đuổi kịp 1 tỷ.
    SCH_tasks_G[Index].NextRunTime = global_tick_count + SCH_tasks_G[Index].Delay;

    return Index;
}

void SCH_Dispatch_Tasks(void) {
    unsigned char Index;

    for (Index = 0; Index < MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].pTask) {
            // Phép so sánh này vẫn đúng tuyệt đối nhờ tính chất Overflow của số nguyên
            // Dù sau khi trừ đi 1 tỷ, giá trị NextRunTime có thể thành số rất lớn (do underflow)
            // nhưng khi ép kiểu (int32_t), hiệu số vẫn ra đúng giá trị âm/dương mong muốn.
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
