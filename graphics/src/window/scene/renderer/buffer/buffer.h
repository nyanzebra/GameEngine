#pragma once

#include <glew.h>
#include <vector>

namespace cppe {
	namespace graphics {
		enum vectorSize {
			ONE = 0x1,
			TWO = 0x2,
			THREE = 0x3,
			FOUR = 0x4,
		};

		class Buffer {
		public:
			Buffer(const float* data, const unsigned int& count, const vectorSize& vector_size);
			~Buffer() { glDeleteBuffers(1, &buffer); }

			virtual void bind() const;
			virtual void unbind() const;

			const vectorSize& getvectorSize() const;
		private:
			GLuint buffer;
			vectorSize vector_size = FOUR;
		};

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