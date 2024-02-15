#include "Tests.hpp"

namespace Hexxy {
	bool vec3_size_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		return (vec.VEC_SIZE() == 3 && sizeof(vec) == sizeof(vec.x) * vec.VEC_SIZE());
	}
	bool vec3_unit_vector_test() {
		Hexxy::Math::Vectors::Vec3 vec = Hexxy::Math::Vectors::Vec3::unit();
		return (vec.x == 1 && vec.y == 1 && vec.z == 1);
	}
	bool vec3_single_value_constructor_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		return (vec.r == 2 && vec.g == 2 && vec.b == 2
			&& vec.x == 2 && vec.y == 2 && vec.z == 2);
	}
	bool vec3_multiple_value_constructor_test() {
		Hexxy::Math::Vectors::Vec3 vec(2, 3, 4);
		return (vec.r == 2 && vec.g == 3 && vec.b == 4
			&& vec.x == 2 && vec.y == 3 && vec.z == 4);
	}
	bool vec3_assignement_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		Hexxy::Math::Vectors::Vec3 vec2(3);
		vec2 = vec;
		vec = Hexxy::Math::Vectors::Vec3(3);
		return (vec.x == 3 && vec.y == 3 && vec.z == 3
			&& vec2.x == 2 && vec2.y == 2 && vec2.z == 2);
	}
	bool vec3_increment_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		Hexxy::Math::Vectors::Vec3 vec2 = ++vec;
		Hexxy::Math::Vectors::Vec3 vec3 = vec++;
		return (vec.x == 4 && vec.y == 4 && vec.z == 4
			&& vec2.x == 3 && vec2.y == 3 && vec2.z == 3
			&& vec3.x == 3 && vec3.y == 3 && vec3.z == 3);
	}
	bool vec3_decrement_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		Hexxy::Math::Vectors::Vec3 vec2 = --vec;
		Hexxy::Math::Vectors::Vec3 vec3 = vec--;
		return (vec.x == 0 && vec.y == 0 && vec.z == 0
			&& vec2.x == 1 && vec2.y == 1 && vec2.z == 1
			&& vec3.x == 1 && vec3.y == 1 && vec3.z == 1);
	}
	bool vec3_addition_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		vec += Hexxy::Math::Vectors::Vec3(2);
		vec += vec;
		vec = vec + vec + vec + Hexxy::Math::Vectors::Vec3(3);
		return (vec.x == 27 && vec.y == 27 && vec.z == 27);
	}
	bool vec3_subtraction_test() {
		Hexxy::Math::Vectors::Vec3 vec(4);
		vec -= Hexxy::Math::Vectors::Vec3(2);
		vec -= vec;
		Hexxy::Math::Vectors::Vec3 vec2(4);
		vec2 = vec2 - vec2 - vec2 - Hexxy::Math::Vectors::Vec3(3);
		return (vec.x == 0 && vec.y == 0 && vec.z == 0
			&& vec2.x == -7 && vec2.y == -7 && vec2.z == -7);
	}
	bool vec3_scalar_multiplication_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		vec *= 2;
		vec = vec * 3;
		return (vec.x == 12 && vec.y == 12 && vec.z == 12);
	}
	bool vec3_scalar_division_test() {
		Hexxy::Math::Vectors::Vec3 vec(12);
		vec /= 2;
		vec = vec / 3;
		return (vec.x == 2 && vec.y == 2 && vec.z == 2);
	}
	bool vec3_dot_product_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		return (vec.dot(vec) == 2 * 2 + 2 * 2 + 2 * 2);
	}
	bool vec3_length_test() {
		Hexxy::Math::Vectors::Vec3 vec(2);
		return (vec.length() == (float)sqrt(2 * 2 + 2 * 2 + 2 * 2));
	}
	bool vec3_normalize_test() {
		Hexxy::Math::Vectors::Vec3 vec(1);
		vec = vec.normalize();
		Hexxy::Math::Vectors::Vec3 vec2(3, 4, 5);
		vec2 = vec2.normalize();
		return (vec.x == 0.5773502691896258f && vec.y == 0.5773502691896258f && vec.z == 0.5773502691896258f
			&& vec2.x == 0.4242640687119285f && vec2.y == 0.565685424949238f && vec2.z == 0.7071067811865475f);
	}
	bool Tests::Hexxy_Tests_Vec3() {
		HEXXY_TEST_START;
		HEXXY_TEST(vec3_size_test);
		HEXXY_TEST(vec3_unit_vector_test);
		HEXXY_TEST(vec3_single_value_constructor_test);
		HEXXY_TEST(vec3_multiple_value_constructor_test);
		HEXXY_TEST(vec3_assignement_test);
		HEXXY_TEST(vec3_increment_test);
		HEXXY_TEST(vec3_decrement_test);
		HEXXY_TEST(vec3_addition_test);
		HEXXY_TEST(vec3_subtraction_test);
		HEXXY_TEST(vec3_scalar_multiplication_test);
		HEXXY_TEST(vec3_scalar_division_test);
		HEXXY_TEST(vec3_dot_product_test);
		HEXXY_TEST(vec3_length_test);
		HEXXY_TEST(vec3_normalize_test);
		HEXXY_TEST_END;
	}
}