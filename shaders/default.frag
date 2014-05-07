#version 330 core
out vec3 color;

in vec3 normal;

void main() {
	float c = dot(normal, vec3(0, sqrt(.5), -sqrt(.5))) * .4 + .1;
	color = vec3(c,c,c);
}