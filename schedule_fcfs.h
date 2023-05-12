#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list 
void add(struct list* list, char *name, int priority, int burst);

// invoke the scheduler
void schedule(struct list* list);
