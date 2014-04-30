CXX = g++
LINKERS = -lSDL
FLAGS = -Wall -g -std=c++11

main: main.o game_loop.o
	$(CXX) $(FLAGS) -o main main.o game_loop.o $(LINKERS)

main.o: main.cpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

game_loop.o: game_loop.cpp game_loop.hpp
	$(CXX) $(FLAGS) -c -o game_loop.o game_loop.cpp

clean:
	@echo "Removing object files"
	@rm --force *.o

all: clean main