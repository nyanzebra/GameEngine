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

			void setUniformFloatx1(const char* uniform_object_name, const float& value);
			void setUniformFloatx2(const char* uniform_object_name, const glm::vec2& value);
			void setUniformFloatx3(const char* uniform_object_name, const glm::vec3& value);
			void setUniformFloatx4(const char* uniform_object_name, const glm::vec4& value);

			void setUniformIntx1(const char* uniform_object_name, const int& value);
			void setUniformIntx2(const char* uniform_object_name, const glm::vec2& value);
			void setUniformIntx3(const char* uniform_object_name, const glm::vec3& value);
			void setUniformIntx4(const char* uniform_object_name, const glm::vec4& value);

			void setUniformUIntx1(const char* uniform_object_name, const unsigned int& value);
			void setUniformUIntx2(const char* uniform_object_name, const glm::vec2& value);
			void setUniformUIntx3(const char* uniform_object_name, const glm::vec3& value);
			void setUniformUIntx4(const char* uniform_object_name, const glm::vec4& value);

            void setUniformMatrix4(const char* uniform_object_name, const glm::mat4& value);

			void setUniformFloatvectorx1(const char* uniform_object_name,
										 const unsigned int& count, 
										 const float* value);
			void setUniformFloatvectorx2(const char* uniform_object_name,
										 const unsigned int& count,
										 const float* value);
			void setUniformFloatvectorx3(const char* uniform_object_name,
										 const unsigned int& count,
										 const float* value);
			void setUniformFloatvectorx4(const char* uniform_object_name,
										 const unsigned int& count,
										 const float* value);

			void setUniformIntvectorx1(const char* uniform_object_name,
									   const unsigned int& count,
								       const int* value);
			void setUniformIntvectorx2(const char* uniform_object_name,
									   const unsigned int& count,
									   const int* value);
			void setUniformIntvectorx3(const char* uniform_object_name,
									   const unsigned int& count,
									   const int* value);
			void setUniformIntvectorx4(const char* uniform_object_name,
									   const unsigned int& count,
									   const int* value);

			void setUniformUIntvectorx1(const char* uniform_object_name, 
										const unsigned int& count,
										const unsigned int* value);
			void setUniformUIntvectorx2(const char* uniform_object_name,
										const unsigned int& count,
										const unsigned int* value);
			void setUniformUIntvectorx3(const char* uniform_object_name,
										const unsigned int& count,
										const unsigned int* value);
			void setUniformUIntvectorx4(const char* uniform_object_name,
										const unsigned int& count,
										const unsigned int* value);



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
