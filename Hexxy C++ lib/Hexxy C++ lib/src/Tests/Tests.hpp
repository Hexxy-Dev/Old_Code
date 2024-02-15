#pragma once

#include "../Hexxy/Hexxy.h"
#include <iostream>

namespace Hexxy {
	class Tests {
	#define HEXXY_TEST_START int tests = 0, passed = 0
	#define HEXXY_TEST_END if(tests == passed) return true; else return false
	#define HEXXY_TEST(X) tests++; if(!X()) puts(#X ## " Failed!"); else passed++
	public:
		static void All_Tests() {
			HEXXY_TEST_START;
			HEXXY_TEST(Hexxy_Tests);
			if (tests == passed) puts("\nALL TESTS PASSED!!\n\n\n");
			else puts("\nTESTS FAILED!!\n\n\n");
		}
	private:
		static bool Hexxy_Tests() {
			HEXXY_TEST_START;
			HEXXY_TEST(Hexxy_Tests_Vec2);
			HEXXY_TEST(Hexxy_Tests_Vec3);
			HEXXY_TEST(Hexxy_Tests_Vec4);
			HEXXY_TEST(Hexxy_Tests_Mat2);
			HEXXY_TEST(Hexxy_Tests_Mat3);
			HEXXY_TEST(Hexxy_Tests_Mat4);
			HEXXY_TEST_END;
		}
		static bool Hexxy_Tests_Vec2();
		static bool Hexxy_Tests_Vec3();
		static bool Hexxy_Tests_Vec4();
		static bool Hexxy_Tests_Mat2();
		static bool Hexxy_Tests_Mat3();
		static bool Hexxy_Tests_Mat4();
	};
}