/**<schedule_priority.c>
 * Author: Salman Haidri
 * Student #: 201906120
 * 
 * This code schedules the tasks according to their priority. It also 
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
void initStartTime(void);

int start_tid = 250;            //Task identifier
int currentTime = 0;            //Current time
int wait_Time = 0;              //Wait Time
int average_TT = 0;             //Average Turnaround time
int response_Time = 0;          //Response Time
int num_Task = 0;               //Number of tasks
struct node *ListOfTask = NULL;

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
    insert(&ListOfTask, t);
}

/**
 * Picks the next task for Priority execution  
 */
Task *pickNextTask(void) {
    Task *highestPriority = ListOfTask->task;
    struct node *tempNode = ListOfTask;
    while(tempNode){
        if(tempNode->task->priority >= highestPriority->priority){
            highestPriority = tempNode->task;
        }
        tempNode = tempNode->next;
    }
    return highestPriority;
}

//invoke the scheduler
void schedule(void) {
    printf("Time\tName\ttid\tBurst duration\n");
    initStartTime();
    while(ListOfTask) {
        Task *t = pickNextTask();
        run(t, t->burst);
        //If start time is -1 then change it to current time and add the current time to the response time.
        if (t->start_Time == -1){
            t->start_Time = currentTime;
            response_Time += currentTime;
        }
        currentTime += t->burst;
        wait_Time += currentTime - t->burst;
        delete(&ListOfTask, t);
        average_TT += currentTime;
    }

    printf("Average turnaround time: %0.2f \n", (double)average_TT/num_Task);
    printf("Average wait time: %0.2f \n", (double)wait_Time/num_Task);
    printf("Average response time: %0.2f\n", (double)response_Time/num_Task);
}

//Initializes the start_time of each task to -1.
void initStartTime(void){
    struct node *temp_node = ListOfTask;
    while(1){
        if(!temp_node){
            break;
        }
        //initializing task to -1.
        temp_node->task->start_Time = -1;
        temp_node = temp_node->next;
    }
}