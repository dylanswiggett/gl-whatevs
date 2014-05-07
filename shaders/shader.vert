#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexTextureUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 cameraMat, projMat, modelMat;

out vec3 normal;

void main() {
	vec4 world_pos = modelMat * vec4(vertexPosition_modelspace, 1);
	world_pos.y += cos(world_pos.x) + sin(world_pos.z);
	gl_Position = projMat * cameraMat * world_pos;
	normal = (modelMat * vec4(vertexNormal + vertexPosition_modelspace, 1) - world_pos).xyz;
}