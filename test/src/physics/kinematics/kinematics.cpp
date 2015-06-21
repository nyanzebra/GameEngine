#include <test/testsuite.h>
#include <rigid_body\rigidbody.h>

using namespace cppe::test;
using namespace physics::physical_object;
using namespace physics::kinematics;

TEST_SUITE(kinematics) {

    TEST("precision position") {
        RigidBody rb;
        rb.position = vector3f(0, 0, 0);
        rb.velocity = vector3f(1, 2, 3);
        rb.acceleration = vector3f(1, 0, 1);

        rb.position.x = precision_position(rb.position.x, rb.velocity.x, rb.acceleration.x, 1.0f);
        rb.position.y = precision_position(rb.position.y, rb.velocity.y, rb.acceleration.y, 1.0f);
        rb.position.z = precision_position(rb.position.z, rb.velocity.z, rb.acceleration.z, 1.0f);

        ASSERT_TRUE((1.5f == rb.position.x));
        ASSERT_TRUE((2.0f == rb.position.y));
        ASSERT_TRUE((3.5f == rb.position.z));
    };

    TEST("precision velocity") {
        RigidBody rb;
        rb.position = vector3f(0, 0, 0);
        rb.velocity = vector3f(1, 2, 3);
        rb.acceleration = vector3f(1, 0, 1);

        rb.velocity.x = precision_velocity(rb.velocity.x, rb.acceleration.x, 1.0f);
        rb.velocity.y = precision_velocity(rb.velocity.y, rb.acceleration.y, 1.0f);
        rb.velocity.z = precision_velocity(rb.velocity.z, rb.acceleration.z, 1.0f);

        ASSERT_TRUE((2.0f == rb.velocity.x));
        ASSERT_TRUE((2.0f == rb.velocity.y));
        ASSERT_TRUE((4.0f == rb.velocity.z));
    };

    TEST("precision acceleration") {
        RigidBody rb;
        rb.position = vector3f(0, 0, 0);
        rb.velocity = vector3f(1, 2, 3);
        rb.acceleration = vector3f(1, 0, 1);
        rb.jerk = vector3f(2, 1, 6);

        rb.acceleration.x = precision_acceleration(rb.acceleration.x, rb.jerk.x, 1.0f);
        rb.acceleration.y = precision_acceleration(rb.acceleration.y, rb.jerk.y, 1.0f);
        rb.acceleration.z = precision_acceleration(rb.acceleration.z, rb.jerk.z, 1.0f);

        ASSERT_TRUE((3.0f == rb.acceleration.x));
        ASSERT_TRUE((1.0f == rb.acceleration.y));
        ASSERT_TRUE((7.0f == rb.acceleration.z));
    };

};
