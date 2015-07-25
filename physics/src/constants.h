#pragma once

#include <glm/glm.hpp>
#include <math.h>

using namespace cppe::math;

#define EARTH_GRAVITY 9.81

#define YOTTA   24
#define ZETTA   21
#define EXA     18
#define PETA    15
#define TERA    12
#define GIGA    9
#define MEGA    6
#define KILO    3
#define HECTO   2
#define DECA    1
#define DECI    -1
#define CENTI   -2
#define MILLI   -3
#define MICRO   -6
#define NANO    -9
#define PICO    -12
#define FEMTO   -15
#define ATTO    -18
#define ZEPTO   -21
#define YOCTO   -24

#define POWER(base, p) pow(base, p)
#define UNIT(prefix, sig) (sig * POWER(10, prefix))

#define DENSITY_AIR 1
#define DENSITY_WATER 1000

namespace physics {
    namespace force {
        inline const float precision_force(const float& mass, const float& acceleration) { return mass * acceleration; }

    }
    namespace kinematics {
        inline const float precision_position(const float& initial_position, const float& velocity, const float& acceleration, const float& time) {
            return initial_position + (velocity * time) + (0.5f * acceleration * time * time);
        }

        inline const float precision_velocity(const float& initial_velocity, const float& acceleration, const float& time) {
            return initial_velocity + acceleration * time;
        }

        inline const float precision_acceleration(const float& initial_acceleration, const float& jerk, const float& time) {
            return initial_acceleration + jerk * time;
        }

        inline void precision_position(glm::vec3& position, const glm::vec3& velocity, const glm::vec3& acceleration, const float& time) {
            position.x = precision_position(position.x, velocity.x, acceleration.x, time);
            position.y = precision_position(position.y, velocity.y, acceleration.y, time);
            position.z = precision_position(position.z, velocity.z, acceleration.z, time);
        }
    }
    namespace collisions {
        struct triangle {
            glm::vec3 central_position;
            glm::vec3 normal_vector;
            float xyz_points[9];
        };

        inline const bool precision_collision(const glm::vec3& collision_normal, const glm::vec3& collision_vector) {
            glm::vec3 resultant = collision_normal + collision_vector;

            if (resultant.x == (float)0 && resultant.y == (float)0 && resultant.z == (float)0) {
                return true;
            }

            return false;
        }
    }
}
