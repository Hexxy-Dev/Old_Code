#include "Tests.h"

TEST_BLOCK(CustomVal)
	TEST_BEGIN(Addition_char, 10)
		CustomVar<char> result;
		char expected;
		result = expected = rand() % std::numeric_limits<char>::max();
		char value = rand() % std::numeric_limits<char>::max();
		result = result + value;
		expected = expected + value;
	TEST_END((int)result.Get(), (int)expected)


	TEST_BEGIN(HMM, 2)
	TEST_END("HMM", "HMM")
	TEST_BEGIN(HMM, 2)
	TEST_END("HMM3", "HMM")
	TEST_BEGIN(HMM, 2)
	TEST_END("HMM", "HMM")
	TEST_BEGIN(HMM, 2)
	TEST_END("HMM3", "HMM")
TEST_BLOCK_END