#version 330 core
layout(location = 0) out vec3 color;

in vec3 normal;

void main() {
	color = abs(normal.xyz);
}