#pragma once

#include "math/vector.h"

using namespace cppe::math;

namespace cppe {
	namespace graphics {

		class GameObject {
		public:
			GameObject() = default;
			GameObject(const vector4f& position, const vector3f& size, const vector4f& color);
			~GameObject() = default;

			const unsigned& getColor() const;
			void setColor(const vector4f& color);


			const vector4f& getPosition() const;
			void setPosition(const vector4f& position);

			const vector3f& getSize() const;
			void setSize(const vector3f& size);

		protected:
			unsigned color;
			vector4f position;
			vector3f size;
		};
	}
}
