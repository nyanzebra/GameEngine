#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "shader/shader.h"
#include "texture/texture.h"
#include "../renderer/buffer/buffer.h"

namespace ftl {
    namespace graphics {
        class material {
        public:
            material() = default;
            material(const texture& texture, const shader& shader) : _texture(texture), _shader(shader) {}
            ~material() = default;

            const ftl::graphics::texture& texture() const;
            const ftl::graphics::shader& shader() const;

            void shader(const ftl::graphics::shader& shader);
            void texture(const ftl::graphics::texture& texture);

        private:
            ftl::graphics::texture _texture;
            ftl::graphics::shader _shader;
        };
    }
}
