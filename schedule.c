#include <stdio.h>
#include "list.h"
#include "schedule.h"
#include "CPU.h"
#include<string.h>

#ifdef _WIN32 || _WIN64
   #include <Windows.h>
#else
   #include <unistd.h>
#endif

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

   return -1;
}

void fcfs(struct list* list) {
   // pegar o primeiro da lista
   // esperar a task acabar
   // ir para o proximo
   printf("\n> Beginning scheduler FCFS:");
   struct node* currentNode;
   while(list->length != 0) {
      currentNode = list->head;
      run(currentNode->task, currentNode->task->burst);

      #ifdef _WIN32 || _WIN64
         Sleep(currentNode->task->burst);
      #else
         usleep(currentNode->task->burst*1000);
      #endif

      printf("Task %s done!\n", currentNode->task->name);
      delete(&list->head, currentNode->task);
      list->length --;
   }
   return;
}
