#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 cameraMat, projMat, modelMat;

void main() {
	gl_Position = (projMat * cameraMat * modelMat) * vec4(vertexPosition_modelspace, 1);
}