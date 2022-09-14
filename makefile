# makefile

CC = g++
CFLAGS = -std=c++11

all: BlocksworldAstar

State.o: State.h State.cpp
	$(CC) -g $(CFLAGS) -c State.cpp

Node.o: Node.h Node.cpp
	$(CC) -g $(CFLAGS) -c Node.cpp

BlocksworldAstar.o: BlocksworldAstar.cpp
	$(CC) -g $(CFLAGS) -c BlocksworldAstar.cpp

BlocksworldAstar: BlocksworldAstar.o State.o Node.o
	$(CC) -static-libstdc++ -g -o BlocksworldAstar BlocksworldAstar.o State.o Node.o

clean:
	rm -rf *.o BlocksworldAstar
