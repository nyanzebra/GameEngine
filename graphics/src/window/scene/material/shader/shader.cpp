#include "shader.h"

#include "extensions/string_extension.h"
#include "extensions/file.h"
#include "extensions/console.h"

#include "../../../../errors/glerror.h"

using namespace ftl::graphics;

bool shader::is_valid(const GLuint& program) const {
    int is_linked = GL_FALSE;

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        cppe::io::console::output_line("program: ", program, " with status of false");
        GLint size = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        program_info(program, size);
        glDeleteProgram(program);
        return false;
    }
    cppe::io::console::output_line("program: ", program, " with status of true");
    return true;
}

void shader::shader_info(const GLuint& shader) const {
    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* error_message = new char[length];
        glGetShaderInfoLog(shader, length, &length, &error_message[0]);
        cppe::io::console::output_line("ERROR: could not compile shader... ", &error_message[0]);
        glDeleteShader(shader);
    } else {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* error_message = new char[length];
        glGetShaderInfoLog(shader, length, &length, &error_message[0]);
        cppe::io::console::output_line(&error_message[0]);
    }
}

void shader::program_info(const GLuint& program, const GLint& size) const {
    GLint length = size;
    char* info = new char[length];
    glGetProgramInfoLog(program, length, &length, info);
    cppe::io::console::output_line("info for ", program, ": ", info);
}

void shader::load(const std::string& vertex, const std::string& fragment) {
    cppe::io::file file_vertex(vertex);
    file_vertex.read();

    std::string data_vertex = file_vertex.data();

    cppe::io::file file_fragment(fragment);
    file_fragment.read();

    std::string data_fragment = file_fragment.data();

    GLuint shader_program = glCreateProgram();

    GLuint shader_vertex = compile_vertex(data_vertex.c_str());
    GLuint shader_fragment = compile_fragment(data_fragment.c_str());

    glAttachShader(shader_program, shader_fragment);
    glAttachShader(shader_program, shader_vertex);

    glLinkProgram(shader_program);
    if (!is_valid(shader_program)) {
        cppe::io::console::output_line("invalid program");
    }

    glDeleteShader(shader_vertex);
    glDeleteShader(shader_fragment);

    _shader = shader_program;
}

void shader::enable() {
    glUseProgram(_shader);
    _is_enabled = true;
}

void shader::disable() {
    glUseProgram(0);
    _is_enabled = false;
}

const bool shader::is_enabled() const {
    return _is_enabled;
}

const GLint shader::uniform_location(const char* uniform_object_name) {
    return glGetUniformLocation(_shader, uniform_object_name);
}

const GLuint shader::compile_vertex(const char* data_vertex) const {
    GLuint shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, &data_vertex, NULL);
    glCompileShader(shader_vertex);

    shader_info(shader_vertex);

    return shader_vertex;
}

const GLuint shader::compile_fragment(const char* data_fragment) const {
    GLuint shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragment, 1, &data_fragment, NULL);
    glCompileShader(shader_fragment);

    shader_info(shader_fragment);

    return shader_fragment;
}

void shader::setUniformFloatx1(const char* uniform_object_name, const float& value) {
    glUniform1f(uniform_location(uniform_object_name), value);
}
void shader::setUniformFloatx2(const char* uniform_object_name, const glm::vec2& value) {
    glUniform2f(uniform_location(uniform_object_name), value.x, value.y);
}
void shader::setUniformFloatx3(const char* uniform_object_name, const glm::vec3& value) {
    glUniform3f(uniform_location(uniform_object_name), value.x, value.y, value.z);
}
void shader::setUniformFloatx4(const char* uniform_object_name, const glm::vec4& value) {
    glUniform4f(uniform_location(uniform_object_name), value.x, value.y, value.z, value.w);
}

void shader::setUniformIntx1(const char* uniform_object_name, const int& value) {
    glUniform1i(uniform_location(uniform_object_name), value);
}
void shader::setUniformIntx2(const char* uniform_object_name, const glm::vec2& value) {
    glUniform2i(uniform_location(uniform_object_name), value.x, value.y);
}
void shader::setUniformIntx3(const char* uniform_object_name, const glm::vec3& value) {
    glUniform3i(uniform_location(uniform_object_name), value.x, value.y, value.z);
}
void shader::setUniformIntx4(const char* uniform_object_name, const glm::vec4& value) {
    glUniform4i(uniform_location(uniform_object_name), value.x, value.y, value.z, value.w);
}

void shader::setUniformUIntx1(const char* uniform_object_name, const unsigned int& value) {
    glUniform1ui(uniform_location(uniform_object_name), value);
}
void shader::setUniformUIntx2(const char* uniform_object_name, const glm::vec2& value) {
    glUniform2ui(uniform_location(uniform_object_name), value.x, value.y);
}
void shader::setUniformUIntx3(const char* uniform_object_name, const glm::vec3& value) {
    glUniform3ui(uniform_location(uniform_object_name), value.x, value.y, value.z);
}
void shader::setUniformUIntx4(const char* uniform_object_name, const glm::vec4& value) {
    glUniform4ui(uniform_location(uniform_object_name), value.x, value.y, value.z, value.w);
}

void shader::setUniformMatrix4(const char* uniform_object_name, const glm::mat4& value) {
    glm::mat4      temp = value;
    glUniformMatrix4fv(uniform_location(uniform_object_name), 1, GL_FALSE, &temp[0][0]);
}

void shader::setUniformFloatvectorx1(const char* uniform_object_name, const unsigned int& count, const float* value) {
    glUniform1fv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformFloatvectorx2(const char* uniform_object_name, const unsigned int& count, const float* value) {
    glUniform2fv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformFloatvectorx3(const char* uniform_object_name, const unsigned int& count, const float* value) {
    glUniform3fv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformFloatvectorx4(const char* uniform_object_name, const unsigned int& count, const float* value) {
    glUniform4fv(uniform_location(uniform_object_name), count, value);
}

void shader::setUniformIntvectorx1(const char* uniform_object_name, const unsigned int& count, const int* value) {
    glUniform1iv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformIntvectorx2(const char* uniform_object_name, const unsigned int& count, const int* value) {
    glUniform2iv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformIntvectorx3(const char* uniform_object_name, const unsigned int& count, const int* value) {
    glUniform3iv(uniform_location(uniform_object_name), count, value);
}
void shader::setUniformIntvectorx4(const char* uniform_object_name, const unsigned int& count, const int* value) {
    glUniform4iv(uniform_location(uniform_object_name), count, value);
}

void shader::setUniformUIntvectorx1(const char* uniform_object_name, const unsigned int& count, const unsigned int* value) {
    glUniform1uiv(uniform_location(uniform_object_name), count, value);

}
void shader::setUniformUIntvectorx2(const char* uniform_object_name, const unsigned int& count, const unsigned int* value) {
    glUniform2uiv(uniform_location(uniform_object_name), count, value);

}
void shader::setUniformUIntvectorx3(const char* uniform_object_name, const unsigned int& count, const unsigned int* value) {
    glUniform3uiv(uniform_location(uniform_object_name), count, value);

}
void shader::setUniformUIntvectorx4(const char* uniform_object_name, const unsigned int& count, const unsigned int* value) {
    glUniform4uiv(uniform_location(uniform_object_name), count, value);

}
