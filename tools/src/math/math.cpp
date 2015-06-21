#include "math.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float cppe::math::to_radians(const float& degrees) {
	return degrees * (M_PI / 180.0f);
}
