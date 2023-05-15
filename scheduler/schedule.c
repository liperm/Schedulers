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

      if (strcmp(type, "rrp") == 0) {
      rrp(list);
      return;
   }

   return -1;
}

void fcfs(struct list* list) {
   printf("\n> Beginning scheduler FCFS:");
   struct node* current;
   while(list->length != 0) {
      current = list->head;
      run(current->task, current->task->burst);

      printf(" -> Task %s done!", current->task->name);
      delete(&list->head, current->task);
      list->length--;
   }
   return;
}

void rr(struct list* list) {
   int slice;
   printf("\n> Beginning scheduler RR:\n");
   struct node* current;
   current = list->head;
   while(list->length != 0) {
      slice = current->task->burst < QUANTUM ?
         current->task->burst : QUANTUM;

      run(current->task, slice);

      current->task->burst -= slice;
      if(current->task->burst <= 0) {
         printf(" -> Task %s done!", current->task->name);
         delete(&list->head, current->task);
         list->length--;
      }
      current = current->next == NULL ? 
            list->head : current->next;
   }
   return;
}

int getGreaterPriority(struct node* head) {
   struct node* current;
   current = head;
   int graterPriority = current->task->priority;

   while(current != NULL) {
      if(current->task->priority < graterPriority) {
         graterPriority = current->task->priority;
      }

      current = current->next;
   }

   return graterPriority;
}

void rrp(struct list* list) {
   int slice;
   struct node* current;
   current = list->head;
   int greaterPriority;

   while(list->length != 0) {
      greaterPriority = getGreaterPriority(list->head);
      if(current->task->priority == greaterPriority) {
         slice = current->task->burst < QUANTUM ?
            current->task->burst : QUANTUM;

         run(current->task, slice);

         current->task->burst -= slice;
         if(current->task->burst <= 0) {
            printf(" -> Task %s done!", current->task->name);
            delete(&list->head, current->task);
            list->length--;
         }
      }

      current = current->next == NULL ? 
            list->head : current->next;
   }

   return;
}
