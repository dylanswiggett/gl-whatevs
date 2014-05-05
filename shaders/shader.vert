#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 cameraMat, projMat, modelMat;

void main() {
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}