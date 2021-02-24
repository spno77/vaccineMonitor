OBJS 	= main.o citizen.o utils.o 
SOURCE	= main.c citizen.c utils.c
HEADER	= citizen.h utils.h
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

clean:
	rm -f $(OBJS) $(OUT)