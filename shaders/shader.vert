#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexTextureUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 cameraMat, projMat, modelMat;

out vec3 normal;

void main() {
	gl_Position = (projMat * cameraMat * modelMat) * vec4(vertexPosition_modelspace, 1);
	normal = vertexNormal;
}