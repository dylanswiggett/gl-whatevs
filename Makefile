CXX = g++
LINKERS = -lSDL2 -lGLEW -lGL
FLAGS = -Wall -g -std=c++11
BULLET = -I../bullet-2.82-r2704/src/

LIBS = main GameLoop GLHandler Model shader_loader ModelInstance Shader Camera \
       GraphicsPipeline FramebufferBinder GameModel GameObject GamePhysicsObject \
       GamePhysicsState

main: $(foreach file, $(LIBS), $(file).o)
	$(CXX) $(FLAGS) -o main $(foreach file, $(LIBS), $(file).o) $(LINKERS)

main.o: main.cpp GameLoop.hpp GLHandler.hpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

GameModel.o: GameModel.cpp GameModel.hpp GameObject.hpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GameModel.o GameLoop.cpp

GameObject.o: GameObject.cpp GameObject.hpp GameObjectPositionUpdateSubscriber.hpp
	$(CXX) $(FLAGS) -c -o GameObject.o GameObject.cpp

GamePhysicsObject.o: GamePhysicsObject.cpp GamePhysicsObject.hpp GameObject.hpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GamePhysicsObject.o GamePhysicsObject.cpp $(BULLET)

GamePhysicsState.o: GamePhysicsState.cpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GamePhysicsState.o GamePhysicsState.cpp

GameLoop.o: GameLoop.cpp GameLoop.hpp GLHandler.hpp shader_loader.hpp GraphicsPipeline.o
	$(CXX) $(FLAGS) -c -o GameLoop.o GameLoop.cpp

GLHandler.o: GLHandler.cpp GLHandler.hpp Model.hpp shader_loader.hpp \
	         Shader.o
	$(CXX) $(FLAGS) -c -o GLHandler.o GLHandler.cpp

Model.o: Model.cpp Model.hpp
	$(CXX) $(FLAGS) -c -o Model.o Model.cpp

ModelInstance.o: ModelInstance.cpp ModelInstance.hpp
	$(CXX) $(FLAGS) -c -o ModelInstance.o ModelInstance.cpp

Shader.o: Shader.cpp Shader.hpp shader_loader.hpp GraphicsPipelineItem.hpp
	$(CXX) $(FLAGS) -c -o Shader.o Shader.cpp

FramebufferBinder.o: FramebufferBinder.cpp FramebufferBinder.hpp GraphicsPipelineItem.hpp
	$(CXX) $(FLAGS) -c -o FramebufferBinder.o FramebufferBinder.cpp

Camera.o: Camera.cpp Camera.hpp
	$(CXX) $(FLAGS) -c -o Camera.o Camera.cpp

GraphicsPipeline.o: GraphicsPipeline.cpp GraphicsPipeline.hpp
	$(CXX) $(FLAGS) -c -o GraphicsPipeline.o GraphicsPipeline.cpp

shader_loader.o: shader_loader.cpp shader_loader.hpp
	$(CXX) $(FLAGS) -c -o shader_loader.o shader_loader.cpp

clean:
	@echo "Removing object files"
	@rm --force *.o

all: clean main