#pragma once

#include <GL/glew.h>
#include <vector>

namespace ftl {
	namespace graphics {
		class IndexBuffer {
		public:
			IndexBuffer(const unsigned int* data, const unsigned int& count);
			~IndexBuffer() = default;

			void bind() const;
			void unbind() const;
		private:
			GLuint buffer;
		};
	}
}