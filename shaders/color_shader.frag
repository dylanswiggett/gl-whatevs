#version 330 core
out vec3 color;

in vec3 normal;

void main() {
	color = abs(normal.xyz);
}