#pragma once

#include <map>
#include <memory>
#include <vector>

#include <extensions/console.h>
#include <math/math.h>

#include "../rigid_body/rigidbody.h"
#include "../constants.h"

using namespace physics::collisions;
using namespace physics::force;
using namespace physics::kinematics;
using namespace cppe::io;

//world object may be observer pattern with many observed subjects and there may be more than one world object
namespace physics {
    namespace physical_object {
        class worldspace {
        public:
            float length, width, height;
            glm::vec3 position;
        };

        class comparator {
        public:
            bool operator()(const worldspace space, const std::unique_ptr<rigidbody> body) {
                float x = body.get()->position.x;
                float y = body.get()->position.y;
                float z = body.get()->position.z;

                if (within_range(space.position.x - (space.length / 2), x, space.position.x + (space.length / 2))) {
                    if (within_range(space.position.y - (space.width / 2), y, space.position.y + (space.width / 2))) {
                        if (within_range(space.position.z - (space.height / 2), z, space.position.z + (space.height / 2))) {
                            return true;
                        }
                    }
                }
                return false;
            }
        };

        typedef std::vector<std::unique_ptr<rigidbody>> unique_rigid_body_list;
        typedef std::vector<std::unique_ptr<worldspace>> unique_space_list;

        class WorldObject {
        public:
            WorldObject() = default;
            ~WorldObject() = default;

            
        
            rigidbody& find_object(const std::string& name);

            //handle the updated positions first... then cache locations and handle collisions
            void handle_collisions(const float& time) {

            }

            void add_object(std::unique_ptr<rigidbody>& rb) { }

        private:
            float length, width, height;
            glm::vec3 position;

            unique_space_list object_containers;
        };
    }
}
