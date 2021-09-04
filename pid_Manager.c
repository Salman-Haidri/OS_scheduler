/**<Question_2.c>
 * Submitted by: Salman Haidri
 * Student #: 201906120
 * 
 * This code initializes a pid and then allocates and returns some pids
 * and also releases the pids.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
void make_List(void);

#define MIN_PID 300
#define MAX_PID 5000

int *toReturn;

typedef struct Linked_List1 {
    int x;
    struct Linked_List1 *next;
} Linked_List;

Linked_List *head;
Linked_List *tail;

int main(void) {
    if (allocate_map() == -1) {
        printf("Data Structure initialization unsuccessful.\n");
    }
    else{
        printf("Data Structure initialization successful.\n");
        make_List();
        printf("\nAllocating the pids.\n");
        for(int i = 0; i <= 10; i++){
            int pid = allocate_pid();
            printf("%d\n", pid);
        }

        // To release the pids
        printf("\nReleased Pids: \n");
        release_pid(450);
        release_pid(3456);
        release_pid(299);
        release_pid(5000);
    }
    return 0;
}
/**
 * Creates and initializes a Linked List for representing pids;
 * returns âˆ’1 if unsuccessful, 1 if successful
 */ 
int allocate_map(void){
    head = NULL;
    tail = NULL;
    if (head == NULL){
        return 1;
    }
    return -1;
}

/**
 * Making a linked list of length of length 4700 each with an 
 * initial value of 0.
 */
void make_List(void){
    for(int i = MIN_PID; i<= MAX_PID; i++){
        if(head == NULL){
            head = (Linked_List *)malloc(sizeof(Linked_List));
            head->x = 0;
            head->next = NULL;
            tail = head;
        }
        else{
            Linked_List *temp_node = (Linked_List *)malloc(sizeof(Linked_List));
            temp_node->x = 0;
            temp_node->next = NULL;
            tail->next = temp_node;
            tail = temp_node;
        }
    }
}

/**
 * Allocates and returns a pid; returns âˆ’1 if unable to allocate a pid
 * Assigns a random number between MIN_PID and MAX_PID.
 */ 
int allocate_pid(void){
    int Rand_num = (rand()%(MAX_PID+1 - MIN_PID)) + MIN_PID;
    Linked_List *temp_node = head;
    for(int i = 0; i < Rand_num; i++){
        
        temp_node = temp_node->next;
    }
    if(temp_node->x == 0){
        temp_node->x = Rand_num;
        return Rand_num;
    }
    else{
        temp_node = head;
        while(temp_node->next != NULL){
            if (temp_node->x == 0){
                temp_node->x = Rand_num;
                return Rand_num;
            }
        }
        return -1;
    }
}

/**
 * Releases a pid. If the pid has no associated process, it relays the message.
 */
void release_pid(int pid){
    if(pid < 300 || pid >5000){
        printf("Pid %d out of range.\n", pid);
    }
    else{
        Linked_List *temp_node = head;
        for(int i = 300; i < pid; i++){
            temp_node = temp_node->next;
        }
        if(temp_node->x != 0){
            temp_node->x = 0;
            printf("Released pid: %d\n", pid);
        }
        else{
            printf("No process associated with pid %d.\n", pid);
        }
    }
}