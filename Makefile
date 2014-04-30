CXX = g++
LINKERS = -lSDL2 -lGLEW -lGL
FLAGS = -Wall -g -std=c++11

main: main.o GameLoop.o GLHandler.o Model.o shader_loader.o
	$(CXX) $(FLAGS) -o main main.o GameLoop.o GLHandler.o \
	                        Model.o shader_loader.o $(LINKERS)

main.o: main.cpp GameLoop.hpp GLHandler.hpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

GameLoop.o: GameLoop.cpp GameLoop.hpp GLHandler.hpp
	$(CXX) $(FLAGS) -c -o GameLoop.o GameLoop.cpp

GLHandler.o: GLHandler.cpp GLHandler.hpp Model.hpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o GLHandler.o GLHandler.cpp

Model.o: Model.cpp Model.hpp
	$(CXX) $(FLAGS) -c -o Model.o Model.cpp

shader_loader.o: shader_loader.cpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o shader_loader.o shader_loader.cpp

clean:
	@echo "Removing object files"
	@rm --force *.o

all: clean main