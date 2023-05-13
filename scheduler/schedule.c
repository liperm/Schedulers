#include <stdlib.h>
#include <stdio.h>
#include "../list/list.h"
#include "schedule.h"
#include "../CPU/CPU.h"
#include<string.h>

// add a task to the list 
void add(struct list* list, char *name, int priority, int burst){
   Task* task = malloc(sizeof(Task));
   task->name = name;
   task->burst = burst;
   task->priority = priority;
   task->tid = list->length + 1;

   if(list->length == 0){
      struct node *newNode = malloc(sizeof(struct node));
      newNode->task = task;
      newNode->next = NULL;
      list->head = newNode;
      list->length++;
      return;
   }

   insert(&list->head, task);
   list->length++;
}

// invoke the scheduler
void schedule(struct list* list, char type[]){
   if (strcmp(type, "fcfs") == 0) {
      fcfs(list);
      return;
   }

   if (strcmp(type, "rr") == 0) {
      rr(list);
      return;
   }

      if (strcmp(type, "rr") == 0) {
      rrp(list);
      return;
   }

   return -1;
}

void fcfs(struct list* list) {
   printf("\n> Beginning scheduler FCFS:");
   struct node* currentNode;
   while(list->length != 0) {
      currentNode = list->head;
      run(currentNode->task, currentNode->task->burst);

      printf(" -> Task %s done!", currentNode->task->name);
      delete(&list->head, currentNode->task);
      list->length--;
   }
   return;
}

void rr(struct list* list) {
   int slice;
   printf("\n> Beginning scheduler RR:\n");
   struct node* currentNode;
   currentNode = list->head;
   while(list->length != 0) {
      slice = currentNode->task->burst < QUANTUM ?
         currentNode->task->burst : QUANTUM;

      run(currentNode->task, slice);

      currentNode->task->burst -= QUANTUM;
      if(currentNode->task->burst <= 0) {
         printf(" -> Task %s done!", currentNode->task->name);
         delete(&list->head, currentNode->task);
         currentNode = list->head;
         list->length--;
      }
      else {
         currentNode = currentNode->next == NULL ? 
            list->head : currentNode->next;
      }
   }
   return;
}

void rrp(struct list* list) {
   return;
}
