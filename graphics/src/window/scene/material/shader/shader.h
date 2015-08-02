#pragma once

#include <string>

#include <glm/glm.hpp>

#ifdef _WIN32
#include "windows.h"
#endif
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace ftl {
    namespace graphics {
        class shader {
        public:
            shader() = default;
            shader(const std::string& vertex, const std::string& fragment) {
                load(vertex, fragment);
            }
            ~shader() { glDeleteProgram(_shader); }

            const GLuint& value() { return _shader; }

            void load(const std::string& vertex, const std::string& fragment);

            void enable();

            const bool is_enabled() const;

            void disable();

            void uniform_floatx1(const char* uniform_object_name, const float& value);
            void uniform_floatx2(const char* uniform_object_name, const glm::vec2& value);
            void uniform_floatx3(const char* uniform_object_name, const glm::vec3& value);
            void uniform_floatx4(const char* uniform_object_name, const glm::vec4& value);

            void uniform_intx1(const char* uniform_object_name, const int& value);
            void uniform_intx2(const char* uniform_object_name, const glm::tvec2<int>& value);
            void uniform_intx3(const char* uniform_object_name, const glm::tvec3<int>& value);
            void uniform_intx4(const char* uniform_object_name, const glm::tvec4<int>& value);

            void uniform_uintx1(const char* uniform_object_name, const unsigned int& value);
            void uniform_uintx2(const char* uniform_object_name, const glm::tvec2<unsigned int>& value);
            void uniform_uintx3(const char* uniform_object_name, const glm::tvec3<unsigned int>& value);
            void uniform_uintx4(const char* uniform_object_name, const glm::tvec4<unsigned int>& value);

            void uniform_matrix4(const char* uniform_object_name, const glm::mat4& value);

            void uniform_float_vectorx1(const char* uniform_object_name, const unsigned int& count, const float* value);
            void uniform_float_vectorx2(const char* uniform_object_name, const unsigned int& count, const float* value);
            void uniform_float_vectorx3(const char* uniform_object_name, const unsigned int& count, const float* value);
            void uniform_float_vectorx4(const char* uniform_object_name, const unsigned int& count, const float* value);

            void uniform_int_vectorx1(const char* uniform_object_name, const unsigned int& count, const int* value);
            void uniform_int_vectorx2(const char* uniform_object_name, const unsigned int& count, const int* value);
            void uniform_int_vectorx3(const char* uniform_object_name, const unsigned int& count, const int* value);
            void uniform_int_vectorx4(const char* uniform_object_name, const unsigned int& count, const int* value);

            void uniform_uint_vectorx1(const char* uniform_object_name, const unsigned int& count, const unsigned int* value);
            void uniform_uint_vectorx2(const char* uniform_object_name, const unsigned int& count, const unsigned int* value);
            void uniform_uint_vectorx3(const char* uniform_object_name, const unsigned int& count, const unsigned int* value);
            void uniform_uint_vectorx4(const char* uniform_object_name, const unsigned int& count, const unsigned int* value);      

        private:
            bool is_valid(const GLuint& program) const;
            void shader_info(const GLuint& shader) const;
            void program_info(const GLuint& program, const GLint& size) const;

            bool _is_enabled;

            GLuint _shader;

            const GLint uniform_location(const char* uniform_object_name);

            const GLuint compile_vertex(const char* data_vertex) const;

            const GLuint compile_fragment(const char* data_fragment) const;
        };
    }
}
