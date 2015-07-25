#version 420 core

layout (location = 0) out vec4 color;

uniform vec4 rgba;
uniform vec2 light_position;

in DATA {
	vec3 position;
	vec2 coordinate;
	float id;
	vec4 color;
    vec3 normal;
} in_data;

uniform sampler2D textures[16];

void main() {
	float intensity = 1.0 / length(in_data.position.xy - light_position);
	vec4 texture_color = in_data.color;
	if (in_data.id > 0.0) {
		int tid = int(in_data.id - 0.5);
		texture_color = in_data.color * texture2D(textures[tid], in_data.coordinate);
	}
	color = texture_color * intensity;
}
