#include "Tests.hpp"

namespace Hexxy {
	bool vec4_size_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		return (vec.VEC_SIZE() == 4 && sizeof(vec) == sizeof(vec.x) * vec.VEC_SIZE());
	}
	bool vec4_unit_vector_test() {
		Hexxy::Math::Vectors::Vec4 vec = Hexxy::Math::Vectors::Vec4::unit();
		return (vec.x == 1 && vec.y == 1 && vec.z == 1 && vec.w == 1);
	}
	bool vec4_single_value_constructor_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		return (vec.r == 2 && vec.g == 2 && vec.b == 2 && vec.a == 2
			&& vec.x == 2 && vec.y == 2 && vec.z == 2 && vec.w == 2);
	}
	bool vec4_multiple_value_constructor_test() {
		Hexxy::Math::Vectors::Vec4 vec(2, 3, 4, 5);
		return (vec.r == 2 && vec.g == 3 && vec.b == 4 && vec.a == 5
			&& vec.x == 2 && vec.y == 3 && vec.z == 4 && vec.w == 5);
	}
	bool vec4_assignement_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		Hexxy::Math::Vectors::Vec4 vec2(3);
		vec2 = vec;
		vec = Hexxy::Math::Vectors::Vec4(3);
		return (vec.x == 3 && vec.y == 3 && vec.z == 3 && vec.w == 3
			&& vec2.x == 2 && vec2.y == 2 && vec2.z == 2 && vec2.w == 2);
	}
	bool vec4_increment_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		Hexxy::Math::Vectors::Vec4 vec2 = ++vec;
		Hexxy::Math::Vectors::Vec4 vec3 = vec++;
		return (vec.x == 4 && vec.y == 4 && vec.z == 4 && vec.w == 4
			&& vec2.x == 3 && vec2.y == 3 && vec2.z == 3 && vec2.w == 3
			&& vec3.x == 3 && vec3.y == 3 && vec3.z == 3 && vec3.w == 3);
	}
	bool vec4_decrement_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		Hexxy::Math::Vectors::Vec4 vec2 = --vec;
		Hexxy::Math::Vectors::Vec4 vec3 = vec--;
		return (vec.x == 0 && vec.y == 0 && vec.z == 0 && vec.w == 0
			&& vec2.x == 1 && vec2.y == 1 && vec2.z == 1 && vec2.w == 1
			&& vec3.x == 1 && vec3.y == 1 && vec3.z == 1 && vec3.w == 1);
	}
	bool vec4_addition_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		vec += Hexxy::Math::Vectors::Vec4(2);
		vec += vec;
		vec = vec + vec + vec + Hexxy::Math::Vectors::Vec4(3);
		return (vec.x == 27 && vec.y == 27 && vec.z == 27 && vec.w == 27);
	}
	bool vec4_subtraction_test() {
		Hexxy::Math::Vectors::Vec4 vec(4);
		vec -= Hexxy::Math::Vectors::Vec4(2);
		vec -= vec;
		Hexxy::Math::Vectors::Vec4 vec2(4);
		vec2 = vec2 - vec2 - vec2 - Hexxy::Math::Vectors::Vec4(3);
		return (vec.x == 0 && vec.y == 0 && vec.z == 0
			&& vec2.x == -7 && vec2.y == -7 && vec2.z == -7 && vec2.w == -7);
	}
	bool vec4_scalar_multiplication_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		vec *= 2;
		vec = vec * 3;
		return (vec.x == 12 && vec.y == 12 && vec.z == 12 && vec.w == 12);
	}
	bool vec4_scalar_division_test() {
		Hexxy::Math::Vectors::Vec4 vec(12);
		vec /= 2;
		vec = vec / 3;
		return (vec.x == 2 && vec.y == 2 && vec.z == 2 && vec.w == 2);
	}
	bool vec4_dot_product_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		return (vec.dot(vec) == 2 * 2 + 2 * 2 + 2 * 2 + 2 * 2);
	}
	bool vec4_length_test() {
		Hexxy::Math::Vectors::Vec4 vec(2);
		return (vec.length() == (float)sqrt(2 * 2 + 2 * 2 + 2 * 2 + 2 * 2));
	}
	bool vec4_normalize_test() {
		Hexxy::Math::Vectors::Vec4 vec(1);
		vec = vec.normalize();
		Hexxy::Math::Vectors::Vec4 vec2(3, 4, 5, 6);
		vec2 = vec2.normalize();
		return (vec.x == 0.5 && vec.y == 0.5 && vec.z == 0.5 && vec.w == 0.5
			&& vec2.x == 0.3234983125420219f && vec2.y == 0.4313310833893625f
			&& vec2.z == 0.5391638542367032f && vec2.w == 0.6469966250840439f);
	}
	bool Tests::Hexxy_Tests_Vec4() {
		HEXXY_TEST_START;
		HEXXY_TEST(vec4_size_test);
		HEXXY_TEST(vec4_unit_vector_test);
		HEXXY_TEST(vec4_single_value_constructor_test);
		HEXXY_TEST(vec4_multiple_value_constructor_test);
		HEXXY_TEST(vec4_assignement_test);
		HEXXY_TEST(vec4_increment_test);
		HEXXY_TEST(vec4_decrement_test);
		HEXXY_TEST(vec4_addition_test);
		HEXXY_TEST(vec4_subtraction_test);
		HEXXY_TEST(vec4_scalar_multiplication_test);
		HEXXY_TEST(vec4_scalar_division_test);
		HEXXY_TEST(vec4_dot_product_test);
		HEXXY_TEST(vec4_length_test);
		HEXXY_TEST(vec4_normalize_test);
		HEXXY_TEST_END;
	}
}