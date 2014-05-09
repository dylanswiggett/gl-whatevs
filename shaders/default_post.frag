#version 330 core

layout(location = 0) out vec3 color;

in vec3 normal;
in vec2 uv;

uniform sampler2D rendered_tex;
uniform sampler2D depth_tex;

void main() {
	// float c = dot(normal, vec3(0, sqrt(.5), -sqrt(.5))) * .4 + .2;
	float x = (float((int(uv.x * 1000)) / 10))/100;
	float y = (float((int(uv.y * 1000)) / 10))/100;
	float c = texture(depth_tex,uv).x;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	// if (c < 1)
	// 	c = 0;
	color = vec3(c,c,c);
	// color = vec3(c,c,c);
	// color = texture(rendered_tex, vec2(x,y)).rgb;
	// color = vec3(0,0,0);
	// float x = uv.x - .01;
	// while (x <= uv.x + .01) {
	// 	float y = uv.y - .01;
	// 	while (y <= uv.y + .01) {
	// 		color += texture(rendered_tex, vec2(clamp(x,0,.9999),clamp(y,0,.9999))).rgb;
	// 		y += .005;
	// 	}
	// 	x += .005;
	// }
	// color = (texture(rendered_tex, uv).rgb + texture(rendered_tex, clamp(uv + vec2(.01,.01), 0.0, .9999)).rgb) / 2;
	// color = color / (5*5);
}