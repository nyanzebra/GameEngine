#include "prototype_test.h"

#include <test/testsuite.h>

using namespace cppe::test;

TEST_SUITE(Prototype) {

    TEST("prototypeyping") {
        Monster* spiderman = new Spider();
        Monster* batman = new Bat();

        spiderman->clone()->method();
        batman->clone()->method();
    };
}
