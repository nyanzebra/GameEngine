#version 420 core

layout (location = 0) out vec4 color;

uniform vec4 rgba;
uniform vec2 light_position;

in DATA {
	vec4 position;
	vec2 texture_coordinates;
	float texture_id;
	vec4 color;
} in_data;

uniform sampler2D textures[16];

void main() {
	float intensity = 1.0 / length(in_data.position.xy - light_position);
	vec4 texture_color = in_data.color;
	if (in_data.texture_id > 0.0) {
		int tid = int(in_data.texture_id - 0.5);
		texture_color = in_data.color * texture(textures[tid], in_data.texture_coordinates);
	}
	color = texture_color * intensity;
}
