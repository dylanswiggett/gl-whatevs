#version 330 core

layout(location = 0) out vec3 color;

in vec3 normal;
in vec2 uv;

uniform sampler2D rendered_tex;

void main() {
	// float c = dot(normal, vec3(0, sqrt(.5), -sqrt(.5))) * .4 + .2;
	color = (texture(rendered_tex, uv).rgb + texture(rendered_tex, uv + vec2(.01,.01)).rgb) / 2;
}