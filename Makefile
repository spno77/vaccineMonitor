OBJS 	= main.o citizen.o utils.o linkedList.o
SOURCE	= main.c citizen.c utils.c linkedList.c
HEADER	= citizen.h utils.h linkedList.h
OUT		= vaccineMonitor
CC		= gcc
FLAGS	= -c -g

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

citizen.o: citizen.c
	$(CC) $(FLAGS) citizen.c

utils.o: utils.c
	$(CC) $(FLAGS) utils.c

linkedList.o: linkedList.c
	$(CC) $(FLAGS) linkedList.c

clean:
	rm -f $(OBJS) $(OUT)