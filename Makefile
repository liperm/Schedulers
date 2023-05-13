# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf bin/schedule
	rm -rf bin/*.o

build: driver.o list.o CPU.o schedule.o
	$(CC) $(CFLAGS) -o bin/schedule bin/driver.o bin/schedule.o bin/list.o bin/CPU.o

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c -o bin/driver.o

schedule.o: scheduler/schedule.c
	$(CC) $(CFLAGS) -c scheduler/schedule.c -o bin/schedule.o

list.o: list/list.c list/list.h
	$(CC) $(CFLAGS) -c list/list.c -o bin/list.o

CPU.o: CPU/CPU.c CPU/CPU.h
	$(CC) $(CFLAGS) -c CPU/CPU.c -o bin/CPU.o 

run:
	./bin/schedule $(file) $(type)
