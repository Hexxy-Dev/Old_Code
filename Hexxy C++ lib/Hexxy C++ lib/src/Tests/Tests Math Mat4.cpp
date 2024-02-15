#include "Tests.hpp"

namespace Hexxy {
	bool mat4_size_test() {
		Hexxy::Math::Matrix::Mat4 mat(2);
		return (mat.MAT_R_SIZE() == 4 && mat.MAT_C_SIZE() == 4
			&& sizeof(mat) == sizeof(mat.x11) * mat.MAT_R_SIZE() * mat.MAT_C_SIZE());
	}
	bool mat4_identity_matrix_test() {
		Hexxy::Math::Matrix::Mat4 mat = Hexxy::Math::Matrix::Mat4::identity();
		return (mat.x11 == 1 && mat.x12 == 1 && mat.x13 == 1 && mat.x14 == 1 &&
				mat.x21 == 1 && mat.x22 == 1 && mat.x23 == 1 && mat.x24 == 1 &&
				mat.x31 == 1 && mat.x32 == 1 && mat.x33 == 1 && mat.x34 == 1 &&
				mat.x41 == 1 && mat.x42 == 1 && mat.x43 == 1 && mat.x44 == 1);
	}
	bool mat4_single_value_constructor_test() {
		Hexxy::Math::Matrix::Mat4 mat(2);
		return (mat.x11 == 2 && mat.x12 == 2 && mat.x13 == 2 && mat.x14 == 2 &&
				mat.x21 == 2 && mat.x22 == 2 && mat.x23 == 2 && mat.x24 == 2 &&
				mat.x31 == 2 && mat.x32 == 2 && mat.x33 == 2 && mat.x34 == 2 &&
				mat.x41 == 2 && mat.x42 == 2 && mat.x43 == 2 && mat.x44 == 2);
	}
	bool mat4_multiple_value_constructor_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		return (mat.x11 == 1 && mat.x12 == 2 && mat.x13 == 3 && mat.x14 == 4 &&
				mat.x21 == 5 && mat.x22 == 6 && mat.x23 == 7 && mat.x24 == 8 &&
				mat.x31 == 9 && mat.x32 == 10 && mat.x33 == 11 && mat.x34 == 12 &&
				mat.x41 == 13 && mat.x42 == 14 && mat.x43 == 15 && mat.x44 == 16);
	}
	bool mat4_assignement_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Hexxy::Math::Matrix::Mat4 mat2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
		mat2 = mat;
		mat = Hexxy::Math::Matrix::Mat4(4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
		return (mat.x11 == 4 && mat.x12 == 5 && mat.x13 == 6 && mat.x14 == 7 &&
				mat.x21 == 8 && mat.x22 == 9 && mat.x23 == 10 && mat.x24 == 11 &&
				mat.x31 == 12 && mat.x32 == 13 && mat.x33 == 14 && mat.x34 == 15 &&
				mat.x41 == 16 && mat.x42 == 17 && mat.x43 == 18 && mat.x44 == 19 &&
				mat2.x11 == 1 && mat2.x12 == 2 && mat2.x13 == 3 && mat2.x14 == 4 &&
				mat2.x21 == 5 && mat2.x22 == 6 && mat2.x23 == 7 && mat2.x24 == 8 &&
				mat2.x31 == 9 && mat2.x32 == 10 && mat2.x33 == 11 && mat2.x34 == 12 &&
				mat2.x41 == 13 && mat2.x42 == 14 && mat2.x43 == 15 && mat2.x44 == 16);
	}
	bool mat4_increment_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Hexxy::Math::Matrix::Mat4 mat2 = ++mat;
		Hexxy::Math::Matrix::Mat4 mat3 = mat++;
		return (mat.x11 == 3 && mat.x12 == 4 && mat.x13 == 5 && mat.x14 == 6 &&
				mat.x21 == 7 && mat.x22 == 8 && mat.x23 == 9 && mat.x24 == 10 &&
				mat.x31 == 11 && mat.x32 == 12 && mat.x33 == 13 && mat.x34 == 14 &&
				mat.x41 == 15 && mat.x42 == 16 && mat.x43 == 17 && mat.x44 == 18 &&
				mat2.x11 == 2 && mat2.x12 == 3 && mat2.x13 == 4 && mat2.x14 == 5 &&
				mat2.x21 == 6 && mat2.x22 == 7 && mat2.x23 == 8 && mat2.x24 == 9 &&
				mat2.x31 == 10 && mat2.x32 == 11 && mat2.x33 == 12 && mat2.x34 == 13 &&
				mat2.x41 == 14 && mat2.x42 == 15 && mat2.x43 == 16 && mat2.x44 == 17 &&
				mat3.x11 == 2 && mat3.x12 == 3 && mat3.x13 == 4 && mat3.x14 == 5 &&
				mat3.x21 == 6 && mat3.x22 == 7 && mat3.x23 == 8 && mat3.x24 == 9 &&
				mat3.x31 == 10 && mat3.x32 == 11 && mat3.x33 == 12 && mat3.x34 == 13 &&
				mat3.x41 == 14 && mat3.x42 == 15 && mat3.x43 == 16 && mat3.x44 == 17);
	}
	bool mat4_decrement_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Hexxy::Math::Matrix::Mat4 mat2 = --mat;
		Hexxy::Math::Matrix::Mat4 mat3 = mat--;
		return (mat.x11 == -1 && mat.x12 == 0 && mat.x13 == 1 && mat.x14 == 2 &&
				mat.x21 == 3 && mat.x22 == 4 && mat.x23 == 5 && mat.x24 == 6 &&
				mat.x31 == 7 && mat.x32 == 8 && mat.x33 == 9 && mat.x34 == 10 &&
				mat.x41 == 11 && mat.x42 == 12 && mat.x43 == 13 && mat.x44 == 14 &&
				mat2.x11 == 0 && mat2.x12 == 1 && mat2.x13 == 2 && mat2.x14 == 3 &&
				mat2.x21 == 4 && mat2.x22 == 5 && mat2.x23 == 6 && mat2.x24 == 7 &&
				mat2.x31 == 8 && mat2.x32 == 9 && mat2.x33 == 10 && mat2.x34 == 11 &&
				mat2.x41 == 12 && mat2.x42 == 13 && mat2.x43 == 14 && mat2.x44 == 15 &&
				mat3.x11 == 0 && mat3.x12 == 1 && mat3.x13 == 2 && mat3.x14 == 3 &&
				mat3.x21 == 4 && mat3.x22 == 5 && mat3.x23 == 6 && mat3.x24 == 7 &&
				mat3.x31 == 8 && mat3.x32 == 9 && mat3.x33 == 10 && mat3.x34 == 11 &&
				mat3.x41 == 12 && mat3.x42 == 13 && mat3.x43 == 14 && mat3.x44 == 15);
	}
	bool mat4_addition_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		mat += Hexxy::Math::Matrix::Mat4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
		mat += mat;
		mat = mat + mat + mat + Hexxy::Math::Matrix::Mat4(4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
		return (mat.x11 == 112 && mat.x12 == 125 && mat.x13 == 138 && mat.x14 == 151 &&
				mat.x21 == 164 && mat.x22 == 177 && mat.x23 == 190 && mat.x24 == 203 &&
				mat.x31 == 216 && mat.x32 == 229 && mat.x33 == 242 && mat.x34 == 255 &&
				mat.x41 == 268 && mat.x42 == 281 && mat.x43 == 294 && mat.x44 == 307);
	}
	bool mat4_subtraction_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		mat -= Hexxy::Math::Matrix::Mat4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
		mat -= mat;
		Hexxy::Math::Matrix::Mat4 mat2(4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
		mat2 = mat2 - mat2 - mat2 - Hexxy::Math::Matrix::Mat4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
		return (mat.x11 == 0 && mat.x12 == 0 && mat.x13 == 0 && mat.x14 == 0 &&
				mat.x21 == 0 && mat.x22 == 0 && mat.x23 == 0 && mat.x24 == 0 &&
				mat.x31 == 0 && mat.x32 == 0 && mat.x33 == 0 && mat.x34 == 0 &&
				mat.x41 == 0 && mat.x42 == 0 && mat.x43 == 0 && mat.x44 == 0 &&
				mat2.x11 == -21 && mat2.x12 == -23 && mat2.x13 == -25 && mat2.x14 == -27 &&
				mat2.x21 == -29 && mat2.x22 == -31 && mat2.x23 == -33 && mat2.x24 == -35 &&
				mat2.x31 == -37 && mat2.x32 == -39 && mat2.x33 == -41 && mat2.x34 == -43 &&
				mat2.x41 == -45 && mat2.x42 == -47 && mat2.x43 == -49 && mat2.x44 == -51);
	}
	bool mat4_scalar_multiplication_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		mat *= 2;
		mat = mat * 3;
		return (mat.x11 == 6 && mat.x12 == 12 && mat.x13 == 18 && mat.x14 == 24 &&
				mat.x21 == 30 && mat.x22 == 36 && mat.x23 == 42 && mat.x24 == 48 &&
				mat.x31 == 54 && mat.x32 == 60 && mat.x33 == 66 && mat.x34 == 72 &&
				mat.x41 == 78 && mat.x42 == 84 && mat.x43 == 90 && mat.x44 == 96);
	}
	bool mat4_mat4_multiplication_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Hexxy::Math::Matrix::Mat4 mat2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
		mat *= mat;
		mat = mat * mat2;
		return (mat.x11 == 9860 && mat.x12 == 10280 && mat.x13 == 10700 && mat.x14 == 11120 &&
				mat.x21 == 22692 && mat.x22 == 23656 && mat.x23 == 24620 && mat.x24 == 25584 &&
				mat.x31 == 35524 && mat.x32 == 37032 && mat.x33 == 38540 && mat.x34 == 40048 &&
				mat.x41 == 48356 && mat.x42 == 50408 && mat.x43 == 52460 && mat.x44 == 54512);
	}
	bool mat4_vec4_multiplication_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Hexxy::Math::Vectors::Vec4 vec(17, 18, 19, 20);
		Hexxy::Math::Vectors::Vec4 vec2 = Hexxy::Math::Vectors::Vec4::unit();
		vec2 = mat * vec;
		return (vec2.x == 190 && vec2.y == 486 && vec2.z == 782 && vec2.w == 1078);
	}
	bool mat4_scalar_division_test() {
		Hexxy::Math::Matrix::Mat4 mat(6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72, 78, 84, 90, 96);
		mat /= 2;
		mat = mat / 3;
		return (mat.x11 == 1 && mat.x12 == 2 && mat.x13 == 3 && mat.x14 == 4 &&
				mat.x21 == 5 && mat.x22 == 6 && mat.x23 == 7 && mat.x24 == 8 &&
				mat.x31 == 9 && mat.x32 == 10 && mat.x33 == 11 && mat.x34 == 12 &&
				mat.x41 == 13 && mat.x42 == 14 && mat.x43 == 15 && mat.x44 == 16);
	}
	bool mat4_determinant_test() {
		Hexxy::Math::Matrix::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		auto det = Hexxy::Math::Matrix::CalculateDeterminant(mat);
		Hexxy::Math::Matrix::Mat4 mat2(4, 2, 4, 2, 2, 5, 2, 4, 4, 2, 6, 2, 2, 4, 2, 4);
		auto det2 = Hexxy::Math::Matrix::CalculateDeterminant(mat2);
		return (det == 0 && det2 == 24);
	}
	bool Tests::Hexxy_Tests_Mat4() {
		HEXXY_TEST_START;
		HEXXY_TEST(mat4_size_test);
		HEXXY_TEST(mat4_identity_matrix_test);
		HEXXY_TEST(mat4_single_value_constructor_test);
		HEXXY_TEST(mat4_multiple_value_constructor_test);
		HEXXY_TEST(mat4_assignement_test);
		HEXXY_TEST(mat4_increment_test);
		HEXXY_TEST(mat4_decrement_test);
		HEXXY_TEST(mat4_addition_test);
		HEXXY_TEST(mat4_subtraction_test);
		HEXXY_TEST(mat4_scalar_multiplication_test);
		HEXXY_TEST(mat4_mat4_multiplication_test);
		HEXXY_TEST(mat4_vec4_multiplication_test);
		HEXXY_TEST(mat4_scalar_division_test);
		HEXXY_TEST(mat4_determinant_test);
		HEXXY_TEST_END;
	}
}