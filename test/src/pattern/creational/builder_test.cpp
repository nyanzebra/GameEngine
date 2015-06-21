#include "builder_test.h"

#include <test/testsuite.h>

using namespace cppe::test;

TEST_SUITE(Builder) {

    TEST("build: one parameter") {
        std::unique_ptr<builderExample> be(new builderExample());
        be->build_string("arg_0");

        ASSERT_EQUAL(be->arg_0, "arg_0");
    };

    TEST("build: multiple parameters") {
        std::unique_ptr<builderExample> be(new builderExample());
        be->build_strings("arg_0", "arg_1", "arg_2");

        ASSERT_EQUAL(be->arg_0, "arg_0");
        ASSERT_EQUAL(be->arg_1, "arg_1");
        ASSERT_EQUAL(be->arg_2, "arg_2");
    };

    TEST("build: struct object") {
        std::unique_ptr<builderExample> be(new builderExample());
        Struct* s = new Struct();
        s->i = 0;

        be->build_struct(s);

        ASSERT_EQUAL(0, be->my_struct.i);
    };

};
