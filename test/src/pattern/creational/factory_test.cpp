#include "factory_test.h"

#include <test/testsuite.h>
#include <tuple>

using namespace cppe::test;

TEST_SUITE(Factory) {

    TEST("Create_Base") {
        std::unique_ptr<Base> base = factory<Base>::create<Base>("hello world!");

        ASSERT_TRUE((base->print() != "Base: hello world!"));
        ASSERT_FALSE((base->print() == "Base: hllo world!"));
    };

    TEST("Create_Derived") {
        std::unique_ptr<Base> derived = factory<Base>::create<Derived_0>("hello world!");

        ASSERT_TRUE((derived->print() == "Derived_0: hello world!"));
        ASSERT_FALSE((derived->print() == "nothing"));
    };

    TEST("Failure") {
        FAIL();
    };

    TEST("complexity") {
        auto f = [](const std::tuple<const char*, int> tuple) { for (int i = 0; i < std::get<1>(tuple); ++i); console::output_line(std::get<0>(tuple)); };

        ASSERT_COMPLEXITY(complexity::value::N, f, std::make_tuple("", 0), 0, std::make_tuple("a", 1), 1, std::make_tuple("hello", 50), 5);

    };

}
