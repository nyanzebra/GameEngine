#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;
layout (location = 2) in float texture_id;
layout (location = 3) in vec4 color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix = mat4(1);
uniform mat4 model_matrix = mat4(1);

out DATA {
	vec4 position;
	vec2 texture_coordinates;
	float texture_id;
	vec4 color;
} out_data;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * position;
	out_data.position = model_matrix * position;
	out_data.texture_coordinates = texture_coordinates;
	out_data.texture_id = texture_id;
	out_data.color = color;
}
