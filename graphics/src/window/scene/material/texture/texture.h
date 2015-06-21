#pragma once

#include <string>
#include <memory>
#include <vector>

#include "../../configurables.h"

#ifdef _WIN32
#include "windows.h"
#endif
#include <glew.h>
#define GLFW_DLL
#include <glfw3.h>

namespace cppe {
	namespace graphics {
		struct Image {
			const char* name;
			unsigned char* data;
			unsigned int width;
			unsigned int height;
			int depth;
			unsigned bits_per_pixel;
		};

		class Texture {
		public:
			Texture() = default;
			Texture(const std::string& resource_name,
					const Dimension& dimension,
					const Aliasing& aliasing,
					const bool& generate_mipmap);
			~Texture() = default;

			const bool load(const std::string& resource_name,
							const Dimension& dimension,
							const Aliasing& aliasing,
							const bool& generate_mipmap);

			const Image& getImage() const;

			const GLuint& getID() const;

			void bind() const;
			void unbind() const;

		private:
			void configure(const Dimension& dimension, const Aliasing& aliasing);
			void configure_dimension(const int& dimension, const Aliasing& aliasing);
			void configure_alias(const int& dimension, const int& aliasing);

			BYTE* load_image(const char* resource_name, unsigned* width, unsigned* height);

			Dimension dimension;
			GLuint texture = 0;
			Image image;
		};
	}
}
