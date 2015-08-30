#include <test/testsuite.h>

#include <extensions/cache.h>
#include <extensions/byte.h>

using namespace cppe::test;
using namespace cppe::memory;

TEST_SUITE(cache_test) {

	TEST("cache") {

		cppe::memory::cache<cache_policy<int, float, 32_byte>> _cache;
		{
			_cache.add(0, 3.14f);
			_cache.add(1, 2.72f);
			_cache.add(2, 3.14f);
			_cache.add(3, 3.14f);
			_cache.add(4, 3.14f); 
			_cache.add(5, 3.14f); 
			_cache.add(6, 3.14f);
			_cache.add(7, 3.14f);
		}
		{			  
			_cache.add(8, 2.72f);
		}
		{
			_cache.swap(0, 1);
		}

		ASSERT_TRUE(_cache.has(3) == true);

		ASSERT_EQUAL(2.72f, _cache[0]);
	};
};

