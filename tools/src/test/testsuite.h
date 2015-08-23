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

            unsigned& passed_tests() { return passes; }
            unsigned& failed_tests() { return fails; }
            unsigned& indeterminates() { return indeterminables; }
            std::string& name() { return suite_name; }
            test_function_map& tests() { return test_map; }
            void current_test_result(const test_result& value) { result = value; }
            const test_result& current_test_result() const { return result; }

            test_function_map test_map;
            std::list<diagnostic_message> diagnostic;

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
        const int are_arrays_not_equal(const T* a, const unsigned long int& sa, const T* b, const unsigned long int& sb) {
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

        template<typename T>
        void assert_array_equal(const T* a, const unsigned long int& sa, const T* b, const unsigned long int& sb) {
            switch (are_arrays_equal((conditional_a), size_a, (conditional_b), size_b)) {
            case -1:
                FAIL_BECAUSE("arrays are of different size"); \
                    break;
            case 0:
                FAIL_BECAUSE("indexed items are different"); \
                    break;
            case 1:
                PASS_BECAUSE("indexed items are the same"); \
                    break;
            default:
                break;
            }
        }

        template<typename T>
        void assert_array_not_equal(const T* a, const unsigned long int& sa, const T* b, const unsigned long int& sb) {
            switch (are_arrays_equal(conditional_a, size_a, conditional_b, size_b)) {
            case -1:
                PASS_BECAUSE("arrays are of different size"); \
                    break;
            case 0:
                FAIL_BECAUSE("indexed items are same"); \
                    break;
            case 1:
                PASS_BECAUSE("indexed items are the different"); \
                    break;
            default:\
                break;
            }
        }

#define ASSERT_ARRAY_EQUAL(conditional_a, size_a, conditional_b, size_b) assert_array_equal((conditional_a),size_a,(conditional_b),size_b))

#define ASSERT_ARRAY_NOT_EQUAL(conditional_a, size_a, conditional_b, size_b) assert_array_not_equal((conditional_a),size_a,(conditional_b),size_b))

#define ASSERT_NULL(conditional) ASSERT((conditional == NULL), " conditional is not NULL")

#define ASSERT_NULLPTR(conditional) ASSERT((conditional == nullptr), " conditional is not a nullptr")

#define ASSERT_NOT_NULL(conditional) ASSERT((conditional != NULL), " conditional is NULL")

#define ASSERT_NOT_NULLPTR(conditional) ASSERT((conditional != nullptr), " conditional is a nullptr")

#define ASSERT_SAME(conditional_a, conditional_b) ASSERT((&conditional_a == &conditional_b), " conditionals are different")

#define ASSERT_DIFFERENT(conditional_a, conditional_b) ASSERT((*conditional_a != &conditional_b), " conditionals are the same")

    }
}

#endif
