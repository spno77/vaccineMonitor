OBJS 	= main.o citizen.o 
SOURCE	= main.c citizen.c 
HEADER	= citizen.h
OUT		= vaccineMonitor
CC		= gcc
FLAGS	= -c -g

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

citizen.o: citizen.c
	$(CC) $(FLAGS) citizen.c

clean:
	rm -f $(OBJS) $(OUT)