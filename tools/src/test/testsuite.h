#pragma once

#include <math.h>
#include <string>
#include <assert.h>

#include "../extensions/color.h"   
#include "../extensions/console.h"
#include "../math/timer.h"

#include "test_registry.h"

using namespace cppe::io;

#ifndef _TEST_
#define _TEST_
namespace cppe {
    namespace test {
        class testsuite {
        public:
            testsuite() = default;
            testsuite(const std::string& name) : testsuite(name, testregistry::instance()) {}
            ~testsuite() = default;
            virtual void init() {}

            inline unsigned& passed_tests() { return passes; }
            inline unsigned& failed_tests() { return fails; }
            inline unsigned& indeterminates() { return indeterminables; }
            inline std::string& name() { return suite_name; }
            inline test_function_map& tests() { return test_map; }
            inline void current_test_result(const test_result& value) { result = value; }
            inline const test_result& current_test_result() const { return result; }

            test_function_map test_map;
            std::list<const diagnostic_message> diagnostic;

        private:
            testsuite(const std::string& name, testregistry& registry) : suite_name(name), registry(registry) {
                this->registry.insert(suite_name, this);
            }

            test_result result = NONE;
            std::string suite_name;
            testregistry& registry;
            unsigned passes = 0;
            unsigned fails = 0;
            unsigned indeterminables = 0;
        };

#define DIAGNOSTIC(message) diagnostic.push_back({__FILE__, __LINE__, message})

#define TEST_SUITE(test_suite)\
        class test_suite : public testsuite {\
        public:\
            test_suite() : testsuite(#test_suite) {}\
            virtual void init() override;\
                                                                        } test_suite_instance;\
        void test_suite::init()

#define TEST(test_name) if(test_map.find(test_name) != test_map.end()) { console::colored_output_line(RED, test_name, " test already exists... undefined behaviour to follow..."); } test_map[test_name] = [=]()

#define ASSERT(condition, message) if (!condition) { current_test_result(FAIL_TEST); DIAGNOSTIC(#condition message); } else { current_test_result(PASS_TEST); DIAGNOSTIC(std::string(message).replace(std::string(message).find("not "), 4, "")); }

#define FAIL() ASSERT(false, " is always false")

#define PASS() ASSERT(true, " should never fail")

#define FAIL_BECAUSE(message) ASSERT(false, message)

#define PASS_BECAUSE(message) ASSERT(true, message)

#define ASSERT_TRUE(condition) ASSERT(condition, " condition is not true")

#define ASSERT_FALSE(condition) ASSERT(!condition, " condition is not false")

#define ASSERT_EQUAL(conditional_a, conditional_b) ASSERT((conditional_a == conditional_b), " conditionals are not equal")

#define ASSERT_NOT_EQUAL(conditional_a, conditional_b) ASSERT((conditional_a != conditional_b), " conditionals are equal")

        template<typename T>
        const int are_arrays_equal(const T* a, const unsigned long int sa, const T* b, const unsigned long int sb) {
            if (sa == sb) {
                for (int i = 0; i < sa; ++i) {
                    if (a[i] != b[i]) {
                        return 0;
                    }
                }
                return 1;
            }
            return -1;
        }

        template<typename T>
        const int are_arrays_not_equal(const T* a, const unsigned long int sa, const T* b, const unsigned long int sb) {
            if (sa == sb) {
                for (int i = 0; i < sa; ++i) {
                    if (a[i] == b[i]) {
                        return 0;
                    }
                }
                return 1;
            }
            return -1;
        }

#define ASSERT_ARRAY_EQUAL(conditional_a, size_a, conditional_b, size_b)\
    switch(are_arrays_equal((conditional_a),size_a,(conditional_b),size_b)){\
    case -1:\
        FAIL_BECAUSE("arrays are of different size");\
        break;\
    case 0:\
        FAIL_BECAUSE("indexed items are different");\
        break;\
    case 1:\
        PASS_BECAUSE("indexed items are the same");\
        break;\
    default:\
        break;\
            }

#define ASSERT_ARRAY_NOT_EQUAL(conditional_a, size_a, conditional_b, size_b)\
    switch(are_arrays_equal(conditional_a,size_a,conditional_b,size_b)){\
    case -1:\
        PASS_BECAUSE("arrays are of different size");\
        break;\
    case 0:\
        FAIL_BECAUSE("indexed items are same");\
        break;\
    case 1:\
        PASS_BECAUSE("indexed items are the different");\
        break;\
    default:\
        break;\
                    }   

#define ASSERT_NULL(conditional) ASSERT((conditional == NULL), " conditional is not NULL")

#define ASSERT_NULLPTR(conditional) ASSERT((conditional == nullptr), " conditional is not a nullptr")

#define ASSERT_NOT_NULL(conditional) ASSERT((conditional != NULL), " conditional is NULL")

#define ASSERT_NOT_NULLPTR(conditional) ASSERT((conditional != nullptr), " conditional is a nullptr")

#define ASSERT_SAME(conditional_a, conditional_b) ASSERT((&conditional_a == &conditional_b), " conditionals are different")

#define ASSERT_DIFFERENT(conditional_a, conditional_b) ASSERT((*conditional_a != &conditional_b), " conditionals are the same")

#define ASSERT_COMPLEXITY(complex, function, base_case, base_amount, k_case, k_amount, n_case, n_amount) {\
        std::string complexity_messages[6] = {\
            "complexity is constant time",\
            "complexity is logn time",\
            "complexity is n time",\
            "complexity is nlogn time",\
            "complexity is n^2 time",\
            "complexity is worse than n^2 time"\
                                        };\
        Timer t;\
        function(base_case);\
        auto t0 = t.time();\
        function(k_case);\
        auto t1 = t.time();\
        function(n_case);\
        auto t2 = t.time();\
        complexity::value c = complexity::find_complexity(t0, base_amount, t1, k_amount, t2, n_amount);\
        if (complex != c) {\
            DIAGNOSITIC(complexity_messages[c].c_str());\
                                        }\
                                }

    }
}
#endif
