#pragma once

#include "math/vector.h"

namespace cppe {
	namespace graphics {

		static const float MaxVerticalAngle = 85;

		class Camera {
		public:
			Camera(const cppe::math::vector2f& position);
			~Camera() {}



		private:

			//glm::vec3 current_position;
			float movement_speed;

		};
	}
}
