#pragma once

#include <string>

#include "math/vector.h"
#include "math/matrix.h"

#ifdef _WIN32
#include "windows.h"
#endif
#include <glew.h>
#define GLFW_DLL
#include <glfw3.h>

using namespace cppe::math;

namespace cppe {
	namespace graphics {
		class Shader {
		public:
			Shader() = default;
			Shader(const std::string& vertex, const std::string& fragment) {
				load(vertex, fragment);
			}
			~Shader() { glDeleteProgram(shader); }

			void load(const std::string& vertex, const std::string& fragment);
			
			void enable();

			const bool isEnabled() const;

			void disable();

			void setUniformFloatx1(const char* uniform_object_name, const float& value);
			void setUniformFloatx2(const char* uniform_object_name, const vector2f& value);
			void setUniformFloatx3(const char* uniform_object_name, const vector3f& value);
			void setUniformFloatx4(const char* uniform_object_name, const vector4f& value);

			void setUniformIntx1(const char* uniform_object_name, const int& value);
			void setUniformIntx2(const char* uniform_object_name, const vector2i& value);
			void setUniformIntx3(const char* uniform_object_name, const vector3i& value);
			void setUniformIntx4(const char* uniform_object_name, const vector4i& value);

			void setUniformUIntx1(const char* uniform_object_name, const unsigned int& value);
			void setUniformUIntx2(const char* uniform_object_name, const vector2i& value);
			void setUniformUIntx3(const char* uniform_object_name, const vector3i& value);
			void setUniformUIntx4(const char* uniform_object_name, const vector4i& value);

			void setUniformMatrix4(const char* uniform_object_name, const matrix4f& value);

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
			bool isValid(const GLuint& program) const;
			void shaderInfo(const GLuint& shader) const;
			void programInfo(const GLuint& program) const;

			bool is_enabled;

			GLuint shader;

			const GLint uniformLocation(const char* uniform_object_name);

			const GLuint compileVertex(const char* data_vertex) const;

			const GLuint compileFragment(const char* data_fragment) const;
		};
	}
}
