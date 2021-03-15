OBJS 	= main.o citizen.o utils.o linkedList.o bloomFilter.o skipList.o stringList.o userCommands.o 
SOURCE	= main.c citizen.c utils.c linkedList.c bloomFilter.c skipList.c stringList.c userCommands.c
HEADER	= citizen.h utils.h linkedList.h bloomFilter.h skipList.h stringList.h userCommands.h
OUT		= vaccineMonitor
CC		= gcc
FLAGS	= -c -g 
LIBS	= -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LIBS)

main.o: main.c
	$(CC) $(FLAGS) main.c

citizen.o: citizen.c
	$(CC) $(FLAGS) citizen.c

utils.o: utils.c
	$(CC) $(FLAGS) utils.c

linkedList.o: linkedList.c
	$(CC) $(FLAGS) linkedList.c

bloomFilter.o: bloomFilter.c
	$(CC) $(FLAGS) bloomFilter.c

skipList.o: skipList.c
	$(CC) $(FLAGS) skipList.c

stringList.o: stringList.c
	$(CC) $(FLAGS) stringList.c

userCommands.o: userCommands.c
	$(CC) $(FLAGS) userCommands.c

clean:
	rm -f $(OBJS) $(OUT)