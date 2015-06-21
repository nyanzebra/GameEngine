#include <test/test_registry.h>
using namespace cppe::test;

int main(int argc, const char* argv[]) {

    testregistry::instance().run_test_suites();

	return 0;
}
