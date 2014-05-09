#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexTextureUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 cameraMat, projMat, modelMat;

out vec3 normal;
out vec2 uv;

uniform sampler2D rendered_tex;
uniform sampler2D depth_tex;


void main() {
	gl_Position = vec4(vertexPosition_modelspace,1);
	uv = (vertexPosition_modelspace.xy + vec2(1,1)) / 2;
	normal = vertexPosition_modelspace;
}