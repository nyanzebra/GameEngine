#pragma once

#include <list>

#include <math/timer.h>

#include "../constants.h"

using namespace physics::collisions;

namespace physics {
    namespace physical_object {
        enum Interpolate {
            NONE,
            INTERPOLATE,
            EXTRAPOLATE,
        };

        enum Dimension {
            TWO,
            MIXED,
            THREE,
        };

        class RigidBody {
        public:
            RigidBody() = default;
            ~RigidBody() = default;

            void handle_collision() { has_collided = true; }
            bool has_collided = false;
            bool should_be_destroyed = false;

            float friction_coefficient;
            float restitution;
            float mass = 0;

            std::list<triangle> triangles;

            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec3 acceleration;
            glm::vec3 jerk;

            Interpolate interpolate = Interpolate::NONE;
            Dimension dimension;

            bool affected_by_gravity = false;
            bool is_movable = false;

            Timer life_span;
        };
    }
}
