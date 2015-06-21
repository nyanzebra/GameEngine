#pragma once

#include <list>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>

#include "../extensions/color.h"   
#include "../extensions/console.h"

using namespace cppe::io;

namespace cppe {
    namespace test {
        typedef std::function<void()> test_function;

        enum test_result {
            NONE,
            PASS_TEST,
            FAIL_TEST,
        };

        

        class complexity {
        public:
            enum value {
                CONSTANT = 0,
                LOG_N = 1,
                N = 2,
                N_LOG_N = 3,
                N_2 = 4,
                WORSE = 5,
            };
            static value find_complexity(const unsigned& t0, const unsigned& n0, const unsigned& t1, const unsigned& n1, const unsigned& t2, const unsigned& n2) {
                if (t0 == t1 && t1 == t2) {
                    return CONSTANT;
                } else if (log((n1 - n0) / (t1 - t0)) == log((n2 - n1) / (t2 - t1))) {
                    return LOG_N;
                } else if (((n1 - n0) / (t1 - t0)) == ((n2 - n1) / (t2 - t1))) {
                    return N;
                } else if (((n1 - n0) / (t1 - t0)) * log((n1 - n0) / (t1 - t0)) == ((n2 - n1) / (t2 - t1)) * log((n2 - n1) / (t2 - t1))) {
                    return N_LOG_N;
                } else if ((((n1 - n0) / (t1 - t0)) * ((n1 - n0) / (t1 - t0))) == ((n2 - n1) / (t2 - t1))) {
                    return N_2;
                } else {
                    return WORSE;
                }
            }
        };

        struct diagnostic_message {
            std::string file;
            int line;
            std::string message;
        };

        typedef std::map<std::string, test_function> test_function_map;

        class testsuite;
        typedef std::map<std::string, testsuite*> test_suite_map;
        //TEST_SUITE_MAP test_suites = {};

        class testregistry {
        public:
            static testregistry& instance() {
                static testregistry instance;
                return instance;
            }
            void run_test_suites();
            void insert(const std::string& name, testsuite* suite) {
                test_suites[name] = suite;
            }
            const bool has_suite(const std::string& name) {
                return (test_suites.find(name) == test_suites.end()) ? false : true;
            }

            testsuite& suite(const std::string& name) { return *test_suites[name]; }

        private:
            test_suite_map test_suites;
            testregistry() = default;
        };

    }
}

