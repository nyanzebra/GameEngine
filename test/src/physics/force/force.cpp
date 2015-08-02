#include <test/testsuite.h>
#include <rigid_body/rigidbody.h>

using namespace cppe::test;
using namespace physics::physical_object;
using namespace physics::force;

TEST_SUITE(force) {

    TEST("precision force") {
        rigidbody rb;
        rb.mass = (float) UNIT(CENTI, 20);
        rb.acceleration = glm::vec3(1, 0, 1);

        glm::vec3 force = glm::vec3(0, 0, 0);

        force.x = precision_force(rb.mass, rb.acceleration.x);
        force.y = precision_force(rb.mass, rb.acceleration.y);
        force.z = precision_force(rb.mass, rb.acceleration.z);

        ASSERT_TRUE((UNIT(CENTI, 20) == force.x));
        ASSERT_TRUE((0.0f == force.y));
        ASSERT_TRUE((UNIT(CENTI, 20) == force.z));
    };

};
