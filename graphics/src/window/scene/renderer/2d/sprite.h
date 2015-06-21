#pragma once

#include <array>

#include "../gameobject.h"
#include "../../material/texture/texture.h"

namespace cppe {
	namespace graphics {
		class Sprite : public GameObject {
		public:
			Sprite(const float& x, const float& y, const float& order, const float& width, const float& height, const vector4f& color)
				: GameObject(vector4f(x, y, order, 0), vector3f(width, height, 0), color) {
				cooridinates[0] = vector2f(0, 0);
				cooridinates[1] = vector2f(0, 1);
				cooridinates[2] = vector2f(1, 1);
				cooridinates[3] = vector2f(1, 0);
			}

			const Texture& getTexture() const;
			void setTexture(const Texture& texture);

			const std::array<vector2f, 4>& getCooridinates() const;
			void setCoordinates(const std::array<vector2f, 4>& cooridinates);

		protected:
			Texture texture;
			std::array<vector2f,4> cooridinates;
		};
	}
}
