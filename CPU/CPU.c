/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include "../task/task.h"

#ifdef _WIN32 || _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

// run this task for the specified time slice
void run(Task *task, int slice) {
    printf(
        "\nRunning task = [%s] [%d] [%d] for %d units",
            task->name, task->priority, task->burst, slice);

    #ifdef _WIN32 || _WIN64
        Sleep(slice);
    #else
        usleep(slice*1000);
    #endif
}
