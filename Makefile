CXX = g++
BULLET = ../bullet-2.82-r2704/src
# Bullet physics linkers are way too large!
LINKERS = -lSDL2 -lGLEW -lGL  -L$(BULLET)/BulletDynamics -lBulletDynamics \
		  -L$(BULLET)/BulletCollision -lBulletCollision -L$(BULLET)/LinearMath -lLinearMath
FLAGS = -Wall -g -std=c++11
BULLET_INCL = -I$(BULLET)

LIBS = main GameLoop GLHandler Model shader_loader ModelInstance Shader Camera \
       GraphicsPipeline FramebufferBinder GameObject  \
       GamePhysicsState GamePhysicsObject GameModel

main: $(foreach file, $(LIBS), $(file).o)
	$(CXX) $(FLAGS) -o main $(foreach file, $(LIBS), $(file).o) $(LINKERS)

main.o: main.cpp GameLoop.hpp GLHandler.hpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

GameModel.o: GameModel.cpp GameModel.hpp GameObject.hpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GameModel.o GameModel.cpp

GameObject.o: GameObject.cpp GameObject.hpp GameObjectPositionUpdateSubscriber.hpp
	$(CXX) $(FLAGS) -c -o GameObject.o GameObject.cpp

GamePhysicsObject.o: GamePhysicsObject.cpp GamePhysicsObject.hpp GameObject.hpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GamePhysicsObject.o GamePhysicsObject.cpp $(BULLET_INCL)

GamePhysicsState.o: GamePhysicsState.cpp GamePhysicsState.hpp
	$(CXX) $(FLAGS) -c -o GamePhysicsState.o GamePhysicsState.cpp $(BULLET_INCL)

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