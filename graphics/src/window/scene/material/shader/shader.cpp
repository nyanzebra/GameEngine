#include "shader.h"

#include "extensions/string_extension.h"
#include "extensions/file.h"
#include "extensions/console.h"

using namespace cppe::graphics;
using namespace cppe::io;

bool Shader::isValid(const GLuint& program) const {
	int params;

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
	console::output_line("program: ", program, " with status of ", params);
	if (params != GL_TRUE) {
		programInfo(program);
		return false;
	}
	return true;
}

void Shader::shaderInfo(const GLuint& shader) const {
	GLint compile_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* error_message = new char[length];
		glGetShaderInfoLog(shader, length, &length, &error_message[0]);
		console::output_line("ERROR: could not compile shader... ", &error_message[0]);
		glDeleteShader(shader);
	}
}

void Shader::programInfo(const GLuint& program) const {
	char info[2048];
	glGetProgramInfoLog(program, 2048, 0, info);
	console::output_line("info for ", program, ": ", info);
}

void Shader::load(const std::string& vertex, const std::string& fragment) {
	file file_vertex(vertex);
	file_vertex.read();

	std::string data_vertex = file_vertex.data();

	file file_fragment(fragment);
	file_fragment.read();

	std::string data_fragment = file_fragment.data();

	GLuint shader_program = glCreateProgram();

	GLuint shader_vertex = compileVertex(data_vertex.c_str());
	GLuint shader_fragment = compileFragment(data_fragment.c_str());

	glAttachShader(shader_program, shader_fragment);
	glAttachShader(shader_program, shader_vertex);

	glLinkProgram(shader_program);
	if (!isValid(shader_program)) {
		console::output_line("invalid program");
	}

	programInfo(shader_program);

	glDeleteShader(shader_vertex);
	glDeleteShader(shader_fragment);

	shader = shader_program;
}

void Shader::enable() {
	glUseProgram(shader);
	is_enabled = true;
}

void Shader::disable() {
	glUseProgram(0);
	is_enabled = false;
}

const bool Shader::isEnabled() const {
	return is_enabled;
}

const GLint Shader::uniformLocation(const char* uniform_object_name) {
	return glGetUniformLocation(shader, uniform_object_name);
}

const GLuint Shader::compileVertex(const char* data_vertex) const {
	GLuint shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_vertex, 1, &data_vertex, NULL);
	glCompileShader(shader_vertex);

	shaderInfo(shader_vertex);

	return shader_vertex;
}

const GLuint Shader::compileFragment(const char* data_fragment) const {
	GLuint shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_fragment, 1, &data_fragment, NULL);
	glCompileShader(shader_fragment);

	shaderInfo(shader_fragment);

	return shader_fragment;
}

void Shader::setUniformFloatx1(const char* uniform_object_name, const float& value) {
	glUniform1f(uniformLocation(uniform_object_name), value);
}
void Shader::setUniformFloatx2(const char* uniform_object_name, const vector2f& value) {
	glUniform2f(uniformLocation(uniform_object_name), value.x, value.y);
}
void Shader::setUniformFloatx3(const char* uniform_object_name, const vector3f& value) {
	glUniform3f(uniformLocation(uniform_object_name), value.x, value.y, value.z);
}
void Shader::setUniformFloatx4(const char* uniform_object_name, const vector4f& value) {
	glUniform4f(uniformLocation(uniform_object_name), value.x, value.y, value.z, value.w);
}

void Shader::setUniformIntx1(const char* uniform_object_name, const int& value) {
	glUniform1i(uniformLocation(uniform_object_name), value);
}
void Shader::setUniformIntx2(const char* uniform_object_name, const vector2i& value) {
	glUniform2i(uniformLocation(uniform_object_name), value.x, value.y);
}
void Shader::setUniformIntx3(const char* uniform_object_name, const vector3i& value) {
	glUniform3i(uniformLocation(uniform_object_name), value.x, value.y, value.z);
}
void Shader::setUniformIntx4(const char* uniform_object_name, const vector4i& value) {
	glUniform4i(uniformLocation(uniform_object_name), value.x, value.y, value.z, value.w);
}

void Shader::setUniformUIntx1(const char* uniform_object_name, const unsigned int& value) {
	glUniform1ui(uniformLocation(uniform_object_name), value);
}
void Shader::setUniformUIntx2(const char* uniform_object_name, const vector2i& value) {
	glUniform2ui(uniformLocation(uniform_object_name), value.x, value.y);
}
void Shader::setUniformUIntx3(const char* uniform_object_name, const vector3i& value) {
	glUniform3ui(uniformLocation(uniform_object_name), value.x, value.y, value.z);
}
void Shader::setUniformUIntx4(const char* uniform_object_name, const vector4i& value) {
	glUniform4ui(uniformLocation(uniform_object_name), value.x, value.y, value.z, value.w);
}

void Shader::setUniformMatrix4(const char* uniform_object_name, const matrix4f& value) {
	glUniformMatrix4fv(uniformLocation(uniform_object_name), 1, GL_FALSE, value.elements);
}

void Shader::setUniformFloatvectorx1(const char* uniform_object_name,
									 const unsigned int& count,
									 const float* value) {
	glUniform1fv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformFloatvectorx2(const char* uniform_object_name,
									 const unsigned int& count,
									 const float* value) {
	glUniform2fv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformFloatvectorx3(const char* uniform_object_name,
									 const unsigned int& count,
									 const float* value) {
	glUniform3fv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformFloatvectorx4(const char* uniform_object_name,
									 const unsigned int& count,
									 const float* value) {
	glUniform4fv(uniformLocation(uniform_object_name), count, value);
}

void Shader::setUniformIntvectorx1(const char* uniform_object_name,
								   const unsigned int& count,
								   const int* value) {
	glUniform1iv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformIntvectorx2(const char* uniform_object_name,
								   const unsigned int& count,
								   const int* value) {
	glUniform2iv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformIntvectorx3(const char* uniform_object_name,
								   const unsigned int& count,
								   const int* value) {
	glUniform3iv(uniformLocation(uniform_object_name), count, value);
}
void Shader::setUniformIntvectorx4(const char* uniform_object_name,
								   const unsigned int& count,
								   const int* value) {
	glUniform4iv(uniformLocation(uniform_object_name), count, value);
}

void Shader::setUniformUIntvectorx1(const char* uniform_object_name,
									const unsigned int& count,
									const unsigned int* value) {
	glUniform1uiv(uniformLocation(uniform_object_name), count, value);

}
void Shader::setUniformUIntvectorx2(const char* uniform_object_name,
									const unsigned int& count,
									const unsigned int* value) {
	glUniform2uiv(uniformLocation(uniform_object_name), count, value);

}
void Shader::setUniformUIntvectorx3(const char* uniform_object_name,
									const unsigned int& count,
									const unsigned int* value) {
	glUniform3uiv(uniformLocation(uniform_object_name), count, value);

}
void Shader::setUniformUIntvectorx4(const char* uniform_object_name,
									const unsigned int& count,
									const unsigned int* value) {
	glUniform4uiv(uniformLocation(uniform_object_name), count, value);

}
