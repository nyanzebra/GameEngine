#include "math.h"

#include <math.h>
#ifndef PI
#define PI_F 3.1415927f
#define PI_DL 3.141592653589793238L;
#define PI_D 3.141592653589793;
#endif

const float to_radians(const float& degrees) {
	return degrees * (PI_F / 180.0f);
}
