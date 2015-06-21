#pragma once

#include "shader/shader.h"
#include "texture/texture.h"
#include "../renderer/buffer/buffer.h"

namespace cppe {
	namespace graphics {
		class Material {
		public:
			Material() = default;
			Material(const Texture& texture, const Shader& shader) :
				texture(texture), shader(shader) {}
			~Material() = default;

			Texture& getTexture();
			Shader& getShader();

			void setShader(const Shader& shader);
			void setTexture(const Texture& texture);

		private:
			Texture texture;
			Shader shader;
		};
	}
}
