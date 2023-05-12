/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedule_fcfs.h"

#define SIZE 100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    struct list* list = malloc(sizeof(list));
    list->length = 0;
    list->head = NULL;

    in = fopen(argv[1],"r");

    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(list, name, priority, burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    printf("\n%d tasks in list", list->length);
    printf("List of tasks:\n");
    traverse(list->head);
    schedule(list);
    printf("\nFinished\n");
    return 0;
}
