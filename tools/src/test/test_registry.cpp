#include "test_registry.h"
#include "testsuite.h"

#include "../extensions/color.h"   
#include "../extensions/console.h"

using namespace cppe::test;
using namespace cppe::io;

inline std::string center(const std::string& name) {
    std::string center = "                                      ";
    center = center.substr(0, 40 - (name.size() / 2));
    center += name;
    return center;
}

inline void print_options() {
    console::output_line("Test Options:");
    console::output_line("c <continue>\t\tto proceed to next suite");
    console::output_line("r <repeat>\t\tto repeat the last test suite");
    console::output_line("s <skip>\t\tto skip the next test suite");
    console::output_line("l <list>\t\tto list the remaining test suites");
    console::output_line("[testsuite]\t\tskips to testsuite, if haven't executed");
    console::output_line("q <quit>\t\tto quit the test suite program");
}

inline bool menu(test_suite_map::iterator& it, const test_suite_map::iterator& end) {
    print_options();
    std::string user_input = "";
    console::input(user_input);

    if (user_input == "c" || user_input == "continue") {
        return true;
    } else if (user_input == "r" || user_input == "repeat") {
        --it;
        return true;
    } else if (user_input == "s" || user_input == "skip") {
        ++it;
        return true;
    } else if (user_input == "q" || user_input == "quit") {
        it = end;
        return false;
    } else if (user_input == "l" || user_input == "list") {
        console::colored_output_line(BLUE, "results: ");
        for (auto begin = it; begin != end; ++begin) {
            console::colored_output_line(BLUE, begin->first);
        }
        console::output_line();
        menu(it, end);
    } else {
        for (auto begin = it; begin != end; ++begin) {
            if (begin->first == user_input) {
                it = begin;
                return true;
            }
        }
        console::output_line("ERROR:\tmust provide valid input");
        menu(it, end);
    }
}

inline void print_header(const std::string& name) {
    console::output_line("================================== TEST SUITE ==================================");
    console::output_line(center(name));
    console::output_line("================================================================================");
}

inline void print_test_header(const std::string& name) {
    console::output_line();
    console::output_line("------------------------------------- TEST -------------------------------------");
    console::output_line(center(name));
    console::output_line("--------------------------------------------------------------------------------");
}

inline void print_footer(testsuite& suite) {
    console::output_line();
    console::output_line("==================================== RESULT ====================================");

    console::colored_output(DARKER(GREEN), "Test(s) passed: ");
    console::colored_output_line(DARKER(GREEN), suite.passed_tests());

    console::colored_output(RED, "Test(s) failed: ");
    console::colored_output_line(RED, suite.failed_tests());

    console::colored_output(BLUE, "Test(s) with unknown result: ");
    console::colored_output_line(BLUE, suite.indeterminates());

    console::output_line("================================================================================");
    console::output_line();
    console::output_line("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    console::output_line();
}

void testregistry::run_test_suites() {
    console::set_color_scheme(WHITE, BLACK);
    for (test_suite_map::iterator test_suite_it = test_suites.begin(); test_suite_it != test_suites.end(); ++test_suite_it) {
        if (menu(test_suite_it, test_suites.end())) {
            print_header(test_suite_it->first);

            test_suite_it->second->init();

            for (test_function_map::iterator test_it = test_suite_it->second->tests().begin(); test_it != test_suite_it->second->tests().end(); ++test_it) {

                print_test_header(test_it->first);

                test_it->second();
                test_result result = test_suite_it->second->current_test_result();

                int i = 0;
                switch (result) {
                case PASS_TEST:
                    test_suite_it->second->passed_tests()++;
                    console::colored_output_line(DARKER(GREEN), "Passed...");
                    break;
                case FAIL_TEST:
                    test_suite_it->second->failed_tests()++;
                    console::colored_output_line(RED, "Failed...");

                    for (diagnostic_message info : test_suite_it->second->diagnostic) {
                        if (i > 0) {
                            console::output_line();
                        }
                        console::colored_output(RED, "file: ");
                        console::colored_output_line(RED, info.file);

                        console::colored_output(RED, "Line number: ");
                        console::colored_output_line(RED, info.line);

                        console::colored_output(RED, "Message: ");
                        console::colored_output_line(RED, info.message);
                        ++i;
                    }

                    test_suite_it->second->diagnostic.clear();
                    break;
                default:
                    test_suite_it->second->indeterminates()++;
                    console::colored_output_line(BLUE, "Indeterminable...");
                    break;
                }
            }

            print_footer(*test_suite_it->second);
        }
    }
}

