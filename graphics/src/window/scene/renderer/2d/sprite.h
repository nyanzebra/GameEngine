#pragma once

#include <array>

#include "../gameobject.h"
#include "../../material/material.h"

namespace ftl {
	namespace graphics {
		class sprite : public game_object {
		public:
			sprite(const glm::vec2& position, const float& order, const glm::vec2& size, const glm::vec4& color)
                : game_object(glm::vec3(position, order), glm::vec3(size, 0), color) {
                _coordinates[0] = glm::vec2(0, 0);
                _coordinates[1] = glm::vec2(0, 1);
                _coordinates[2] = glm::vec2(1, 1);
                _coordinates[3] = glm::vec2(1, 0);
			}

			
            void texture(const ftl::graphics::texture& texture);
            const ftl::graphics::texture& texture() const;

            const std::array<glm::vec2, 4>& coordinates() const;
            void coordinates(const std::array<glm::vec2, 4>& coordinates);

		protected:
            ftl::graphics::texture _texture;
            std::array<glm::vec2, 4> _coordinates;
		};
	}
}
