/**
 * list data structure containing the tasks in the system
 */

#include "../task/task.h"

struct node {
    Task *task;
    struct node *next;
};

struct list
{
    struct node *head;
    int length;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);
