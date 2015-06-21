#include <math/quaternion.h>

#include <test/testsuite.h>

using namespace cppe::test;
using namespace cppe::math;

TEST_SUITE(Quaternion) {

    TEST("add") {
        quaternionf qf_0 = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf qf_1 = quaternionf(vector4f(1, 2, 3, 2));
        quaternionf qf_2 = qf_0 + qf_1;

        quaternionf testant = quaternionf(vector4f(2, 4, 0, 4));

        ASSERT_EQUAL(qf_2, testant);
    };

    TEST("subtract") {
        quaternionf qf_0 = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf qf_1 = quaternionf(vector4f(1, 2, 3, 2));
        quaternionf qf_2 = qf_0 - qf_1;

        quaternionf testant = quaternionf(vector4f(0, 0, -6, 0));

        ASSERT_EQUAL(qf_2, testant);
    };

    TEST("multiply") {
        quaternionf qf_0 = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf qf_1 = quaternionf(vector4f(1, 2, 3, 2));

        quaternionf qf_2 = qf_0 * qf_1;
        quaternionf qf_3 = qf_1 * qf_0;

        console::output_line(qf_2, "\n", qf_3);

        quaternionf testant_0 = quaternionf(vector4f(2, 8, 16, 0));
        quaternionf testant_1 = quaternionf(vector4f(14, 8, -8, 0));

        console::output_line(testant_0, "\n", testant_1);

        ASSERT_EQUAL(qf_2, testant_0);
        ASSERT_EQUAL(qf_3, testant_1);
    };

    TEST("divide") {
        quaternionf qf_0 = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf qf_1 = quaternionf(vector4f(1, 2, 3, 2));

        quaternionf qf_2 = qf_0 / qf_1;
        quaternionf qf_3 = qf_1 / qf_0;

        console::output_line(qf_2, "\n", qf_3);

        quaternionf testant_0 = quaternionf(vector4f(-2.82843f, 0.0f, -2.82843f, 1.41421f));
        quaternionf testant_1 = quaternionf(vector4f(2.82843f, 0.0f, 2.82843f, -1.41421f));

        ASSERT_EQUAL(qf_2, testant_0);
        ASSERT_EQUAL(qf_3, testant_1);
    };

    TEST("unit") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));

        //ASSERT_EQUAL(d, c);

    };

    TEST("conjugate") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));

        quaternionf testant = quaternionf(vector4f(-1, -2, 3, 2));

        ASSERT_EQUAL(qf.conjugate(), testant);
    };

    TEST("inverse") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));

        //ASSERT_EQUAL(d, c);

    };

    TEST("scale") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf scaled = qf.scale(2);

        quaternionf testant = quaternionf(vector4f(2, 4, -6, 4));

        ASSERT_EQUAL(scaled, testant);
    };

    TEST("rotation") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));
        quaternionf testant = quaternionf(vector4f(2, 4, -6, 4));
        //ASSERT_EQUAL(d, c);  
    };

    TEST("norm") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));
        float norm = qf.norm();
        float testant = 18.0f;

        ASSERT_EQUAL(norm, testant);
    };

    TEST("magnitude") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));
        float magnitude = qf.magnitude();
        console::output_line(magnitude);
        float testant = 4.24264;

        ASSERT_EQUAL(magnitude, testant);
    };

    TEST("matrix") {
        quaternionf qf = quaternionf(vector4f(1, 2, -3, 2));

        //ASSERT_EQUAL(d, c);

    };
};
