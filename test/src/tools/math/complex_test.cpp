#include <math/complex.h>

#include <test/testsuite.h>

using namespace cppe::test;
using namespace cppe::math;

TEST_SUITE(Complex) {

    TEST("add") {
        complexi a(1, 3);
        complexi b(-5, 2);
        complexi c = a + b;
        complexi d(-4, 5);

        ASSERT_EQUAL(d, c);
    };

    TEST("subtract") {
        complexi a(1, 3);
        complexi b(-5, 2);
        complexi c = a - b;
        complexi d(6, 1);

        ASSERT_EQUAL(d, c);
    };

    TEST("multiply") {
        complexi a(1, 3);
        complexi b(-5, 2);
        complexi c = a * b;
        complexi d(-11, -13);

        ASSERT_EQUAL(d, c);
    };

    TEST("divide") {
        complexi a(4, 2);
        complexi b(3, -1);
        complexi c = a / b;
        complexi d(1, 1);

        ASSERT_EQUAL(d, c);

    };
};
