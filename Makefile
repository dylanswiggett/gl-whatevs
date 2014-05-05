CXX = g++
LINKERS = -lSDL2 -lGLEW -lGL
FLAGS = -Wall -g -std=c++11

main: main.o GameLoop.o GLHandler.o Model.o shader_loader.o
	$(CXX) $(FLAGS) -o main main.o GameLoop.o GLHandler.o \
	                        Model.o shader_loader.o ModelInstance.o \
	                        $(LINKERS)

main.o: main.cpp GameLoop.hpp GLHandler.hpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

GameLoop.o: GameLoop.cpp GameLoop.hpp GLHandler.hpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o GameLoop.o GameLoop.cpp

GLHandler.o: GLHandler.cpp GLHandler.hpp Model.hpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o GLHandler.o GLHandler.cpp

Model.o: Model.cpp Model.hpp
	$(CXX) $(FLAGS) -c -o Model.o Model.cpp

ModelInstance.o: ModelInstance.cpp ModelInstance.hpp
	$(CXX) $(FLAGS) -c -o ModelInstance.o ModelInstance.hpp

Shader.o: Shader.cpp Shader.hpp
	$(CXX) $(FLAGS) -c -o Shader.o Shader.hpp

Camera.o: Camera.cpp Camera.hpp
	$(CXX) $(FLAGS) -c -o Camera.o Camera.hpp

GameState.o: GameState.cpp GameState.hpp
	$(CXX) $(FLAGS) -c -o GameState.o GameState.hpp

shader_loader.o: shader_loader.cpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o shader_loader.o shader_loader.cpp

clean:
	@echo "Removing object files"
	@rm --force *.o

all: clean main