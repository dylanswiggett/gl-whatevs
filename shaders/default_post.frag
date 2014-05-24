#version 330 core

layout(location = 0) out vec3 color;

in vec3 normal;
in vec2 uv;

uniform sampler2D rendered_tex;
uniform sampler2D depth_tex;

void main() {
	// float c = dot(normal, vec3(0, sqrt(.5), -sqrt(.5))) * .4 + .2;
	// float x = (float((int(uv.x * 1000)) / 10))/100;
	// float y = (float((int(uv.y * 1000)) / 10))/100;
	float depth = texture(depth_tex,uv).x;
	float c = depth;
	// // Agh
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	c = c * c;
	if (c == 1)
		c = .1;
	else
		c -= .1;
	// c = 1 - c;
	// // if (c < 1)
	// // 	c = 0;
	// // color = c * texture(rendered_tex, uv).rgb + vec3(.2, .2, .2) * (1-c);
	// // color = vec3(c,c,c);
	// color = texture(rendered_tex, vec2(x,y)).rgb;
	color = vec3(0,0,0);
	// c = c * .1;

	int amt = 1;
	int num_samples = 0;

	float diff = c * .01;
	for (int i = -amt; i <= amt; i++) {
		for (int j = -amt; j <= amt; j++) {
			float x = clamp(uv.x + diff * i,0,.9999);
			float y = clamp(uv.y + diff * j,0,.9999);
			// float depth_at_sample = texture(depth_tex,vec2(x,y)).x;
			// if (depth_at_sample - depth < .00005) {
				color += texture(rendered_tex, vec2(x,y)).rgb;
				num_samples++;
			// }
		}
	}
	// while (x < uv.x + diff) {
	// 	float y = uv.y - diff;
	// 	while (y < uv.y + diff) {
	// 		color += texture(rendered_tex, vec2(clamp(x,0,.9999),clamp(y,0,.9999))).rgb;
	// 		y += diff;
	// 	}
	// 	x += diff;
	// }
	// // color = (texture(rendered_tex, uv).rgb + texture(rendered_tex, clamp(uv + vec2(.01,.01), 0.0, .9999)).rgb) / 2;
	color = color / num_samples;
	// color = texture(rendered_tex, uv).rgb;
}