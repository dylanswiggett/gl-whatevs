CXX = g++
LINKERS = -lSDL
FLAGS = -Wall -g -std=c++11

main: main.o
	$(CXX) $(FLAGS) -o main main.o $(LINKERS)

main.o: main.cpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

clean:
	@echo "Removing object files"
	@rm --force *.o

all: clean main