OBJS	= main.o graph.o
SOURCE	= main.cpp graph.cpp
HEADER	= graph.hpp
OUT	= graph-traversal
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

graph.o: graph.cpp
	$(CC) $(FLAGS) graph.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
