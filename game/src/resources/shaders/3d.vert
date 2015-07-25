#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coordinate;
layout (location = 2) in float id;
layout (location = 3) in vec4 color;
layout (location = 4) in vec3 normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix = mat4(1);
uniform mat4 model_matrix = mat4(1);

out DATA {
	vec3 position;
	vec2 coordinate;
	float id;
	vec4 color; 
    vec3 normal;
} out_data;

void main() {
    mat4 mvp = projection_matrix * view_matrix * model_matrix;
	gl_Position = mvp * vec4(position, 1);
	out_data.position = (model_matrix * vec4(position, 1)).xyz;
	out_data.coordinate = coordinate;
    out_data.normal = normal;
	out_data.id = id;
	out_data.color = color;
}
