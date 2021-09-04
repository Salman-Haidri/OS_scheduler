/**<schedule_fcfs.c>
 * Author: Salman Haidri
 * Student #: 201906120
 * 
 * This code schedules the tasks according to first-come, First-serve basis. It also 
 * computes the average turaround time, wait time and response time. 
 */

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

void add(char *, int, int);
Task *pickNextTask(void);
void schedule(void);

int start_tid = 250;            //Task identifier
int currentTime = 0;            //Current time
int wait_Time = 0;              //Wait Time
int average_TT = 0;             //Average Turnaround time
int num_Task = 0;
struct node *LIstOfTask = NULL;

// add a task to the list of tasks.
void add(char *name, int priority, int burst) {
    Task *t = malloc(sizeof(Task));
    // assigning the name by first allocating the memory
    t->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(t->name, name);
    //Assigning priority
    t->priority = priority;     
    //Assigning a unique identifier to each task
    t->tid = start_tid;
    start_tid++;                // incrementing  the identifier
    t->burst = burst;           // assigning burst
    num_Task++;                 // incrementing the number of task
    // insert the task into the list of tasks
    insert(&LIstOfTask, t);
}

/**
 * Picks the next task for FCFS execution  
 */
Task *pickNextTask(void) {
    struct node *tempNode = LIstOfTask;
    while(1) {
        if(!tempNode->next) {
            break;
        }
        tempNode = tempNode->next;
    }
    return tempNode->task;
}

//invoke the scheduler
void schedule(void) {
    printf("Time\tName\ttid\tBurst duration\n");
    while(LIstOfTask) {
        Task *t = pickNextTask();
        currentTime += t->burst;
        wait_Time += currentTime - t->burst;
        run(t, t->burst);
        t->tid = 0;
        delete(&LIstOfTask, t);
        average_TT += currentTime;
    }

    printf("Average turnaround time: %0.2f \n", (double)average_TT/num_Task);
    printf("Average wait time: %0.2f \n", (double)wait_Time/num_Task);
    //wait time is same as response time here as they all arrive at time 0
    printf("Average response time: %0.2f\n", (double)wait_Time/num_Task);

}