#include <test/testsuite.h>
#include <rigid_body/rigidbody.h>
#include <mesh/world_object.h>

using namespace cppe::test;
using namespace physics::physical_object;
using namespace physics::kinematics;
using namespace physics::collisions;

TEST_SUITE(collision) {

    TEST("precision collision") {
        /*std::unique_ptr<RigidBody> rb(new RigidBody());
        rb->position = vector3f(0, 0, 0);
        rb->velocity = vector3f(1, 1, 0);
        rb->acceleration = vector3f(0, 0, 0);

        WorldObject world;
        world.add_object(rb);       

        std::unique_ptr<RigidBody> sb(new RigidBody());
        sb->position = vector3f(2, 2, 0);
        sb->velocity = vector3f(-1, -1, 0);
        sb->acceleration = vector3f(0, 0, 0);

        world.add_object(sb);

        Timer timer;
        int i = 0;
        world.handle_collisions(i++);
        while (!sb->has_collided) {
            world.handle_collisions(i++);
        }*/

        //ASSERT_TRUE((1.5f == rb.position.x));
        //ASSERT_TRUE((2.0f == rb.position.y));
        //ASSERT_TRUE((3.5f == rb.position.z));
        PASS();
    };

};
