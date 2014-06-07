#version 330 core

layout(location = 0) out vec3 color;

in vec3 normal;
in vec2 uv;

uniform sampler2D rendered_tex;

void main() {
	vec3 minVals = vec3(1,1,1);
	vec3 maxVals = vec3(0,0,0);

	int num_samples = 0;

	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			float x = clamp(uv.x + i * .0005,0,.9999);
			float y = clamp(uv.y + j * .0005,0,.9999);
			vec3 sample = texture(rendered_tex, vec2(x,y)).rgb;
			minVals = min(minVals, sample);
			maxVals = max(maxVals, sample);
			num_samples++;
		}
	}

	// if (length(maxVals - minVals) > .1)
	// 	color = vec3(0,0,0);
	// else
	// 	color = vec3(1,1,1);
	color = (vec3(1,1,1) - (maxVals - minVals));
}