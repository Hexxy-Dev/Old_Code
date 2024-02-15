#include "Tests.hpp"

namespace Hexxy {
	bool vec2_size_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		return (vec.VEC_SIZE() == 2 && sizeof(vec) == sizeof(vec.x) * vec.VEC_SIZE());
	}
	bool vec2_unit_vector_test() {
		Hexxy::Math::Vectors::Vec2 vec = Hexxy::Math::Vectors::Vec2::unit();
		return (vec.x == 1 && vec.y == 1);
	}
	bool vec2_single_value_constructor_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		return (vec.r == 2 && vec.t == 2 && vec.x == 2 && vec.y == 2);
	}
	bool vec2_multiple_value_constructor_test() {
		Hexxy::Math::Vectors::Vec2 vec(2, 3);
		return (vec.r == 2 && vec.t == 3 && vec.x == 2 && vec.y == 3);
	}
	bool vec2_assignement_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		Hexxy::Math::Vectors::Vec2 vec2(3);
		vec2 = vec;
		vec = Hexxy::Math::Vectors::Vec2(3);
		return (vec.x == 3 && vec.y == 3 && vec2.x == 2 && vec2.y == 2);
	}
	bool vec2_increment_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		Hexxy::Math::Vectors::Vec2 vec2 = ++vec;
		Hexxy::Math::Vectors::Vec2 vec3 = vec++;
		return (vec.x == 4 && vec.y == 4 && vec2.x == 3 && vec2.y == 3 && vec3.x == 3 && vec3.y == 3);
	}
	bool vec2_decrement_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		Hexxy::Math::Vectors::Vec2 vec2 = --vec;
		Hexxy::Math::Vectors::Vec2 vec3 = vec--;
		return (vec.x == 0 && vec.y == 0 && vec2.x == 1 && vec2.y == 1 && vec3.x == 1 && vec3.y == 1);
	}
	bool vec2_addition_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		vec += Hexxy::Math::Vectors::Vec2(2);
		vec += vec;
		vec = vec + vec + vec + Hexxy::Math::Vectors::Vec2(3);
		return (vec.x == 27 && vec.y == 27);
	}
	bool vec2_subtraction_test() {
		Hexxy::Math::Vectors::Vec2 vec(4);
		vec -= Hexxy::Math::Vectors::Vec2(2);
		vec -= vec;
		Hexxy::Math::Vectors::Vec2 vec2(4);
		vec2 = vec2 - vec2 - vec2 - Hexxy::Math::Vectors::Vec2(3);
		return (vec.x == 0 && vec.y == 0 && vec2.x == -7 && vec2.y == -7);
	}
	bool vec2_scalar_multiplication_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		vec *= 2;
		vec = vec * 3;
		return (vec.x == 12 && vec.y == 12);
	}
	bool vec2_scalar_division_test() {
		Hexxy::Math::Vectors::Vec2 vec(12);
		vec /= 2;
		vec = vec / 3;
		return (vec.x == 2 && vec.y == 2);
	}
	bool vec2_dot_product_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		return (vec.dot(vec) == 2 * 2 + 2 * 2);
	}
	bool vec2_length_test() {
		Hexxy::Math::Vectors::Vec2 vec(2);
		return (vec.length() == (float)sqrt(2 * 2 + 2 * 2));
	}
	bool vec2_normalize_test() {
		Hexxy::Math::Vectors::Vec2 vec(1);
		vec = vec.normalize();
		Hexxy::Math::Vectors::Vec2 vec2(3, 4);
		vec2 = vec2.normalize();
		return (vec.x == 0.7071067811865475f && vec.y == 0.7071067811865475f
			&& vec2.x == 0.6f && vec2.y == 0.8f);
	}
	bool vec2_angle_test() {
		Hexxy::Math::Vectors::Vec2 vec(0.5, 0.5);
		vec = vec.normalize();
		return (vec.angle_degrees() == 45);
	}
	bool Tests::Hexxy_Tests_Vec2() {
		HEXXY_TEST_START;
		HEXXY_TEST(vec2_size_test);
		HEXXY_TEST(vec2_unit_vector_test);
		HEXXY_TEST(vec2_single_value_constructor_test);
		HEXXY_TEST(vec2_multiple_value_constructor_test);
		HEXXY_TEST(vec2_assignement_test);
		HEXXY_TEST(vec2_increment_test);
		HEXXY_TEST(vec2_decrement_test);
		HEXXY_TEST(vec2_addition_test);
		HEXXY_TEST(vec2_subtraction_test);
		HEXXY_TEST(vec2_scalar_multiplication_test);
		HEXXY_TEST(vec2_scalar_division_test);
		HEXXY_TEST(vec2_dot_product_test);
		HEXXY_TEST(vec2_length_test);
		HEXXY_TEST(vec2_normalize_test);
		HEXXY_TEST(vec2_angle_test);
		HEXXY_TEST_END;
	}
}