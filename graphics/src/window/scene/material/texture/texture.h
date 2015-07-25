#pragma once

#include <string>
#include <memory>
#include <vector>

#include "../../configurables.h"

#ifdef _WIN32
#include "windows.h"
#endif
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace ftl {
	namespace graphics {
		struct image {
			const char* _name;
			unsigned char* _data;
			unsigned int _width;
			unsigned int _height;
			int _depth;
			unsigned _bits_per_pixel;
		};

		class texture {
		public:
			texture() = default;
			texture(const std::string& resource_name,
					const Dimension& dimension,
					const Aliasing& aliasing,
					const bool& generate_mipmap);
			~texture() = default;

			const bool load(const std::string& resource_name,
							const Dimension& dimension,
							const Aliasing& aliasing,
							const bool& generate_mipmap);

			const image& image() const;

			const GLuint& ID() const;

			void bind() const;
			void unbind() const;

		private:
			void configure(const Dimension& dimension, const Aliasing& aliasing);
			void configure_dimension(const int& dimension, const Aliasing& aliasing);
			void configure_alias(const int& dimension, const int& aliasing);

			BYTE* load_image(const char* resource_name, unsigned* width, unsigned* height);

			Dimension _dimension;
			GLuint _texture = 0;
			ftl::graphics::image _image;
		};
	}
}
