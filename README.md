# Schedulers

# To Run
## 1° - Build the project
Build the project with `make build`;

## 2° - Run 
Run with `./bin/schedule [TEXT_FILE] [SCHEDULE_TYPE]`;

Text file should be the name of the file containing the tasks (eg.: tasks.txt).

Schedule type should be onde of the following:
* `fcfs`: run the First-Come, First-Served algorithm;
* `rr`: run the Round Robin algorithm;
* `rrp`: run the Round Robin algorithm with priority;
