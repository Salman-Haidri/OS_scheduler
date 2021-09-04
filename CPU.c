/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"
#include "cpu.h"
int current_Time = 0;
// run this task for the specified time slice
void run(Task *task, int slice) {
    printf("%d\t%s\t%d\t%d\n",current_Time, task->name, task->tid, task->burst);
    current_Time += slice;
}