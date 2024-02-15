#include "Tests.hpp"

namespace Hexxy {
	bool mat3_size_test() {
		Hexxy::Math::Matrix::Mat3 mat(2);
		return (mat.MAT_R_SIZE() == 3 && mat.MAT_C_SIZE() == 3
			&& sizeof(mat) == sizeof(mat.x11) * mat.MAT_R_SIZE() * mat.MAT_C_SIZE());
	}
	bool mat3_identity_matrix_test() {
		Hexxy::Math::Matrix::Mat3 mat = Hexxy::Math::Matrix::Mat3::identity();
		return (mat.x11 == 1 && mat.x12 == 1 && mat.x13 == 1 &&
				mat.x21 == 1 && mat.x22 == 1 && mat.x23 == 1 &&
				mat.x31 == 1 && mat.x32 == 1 && mat.x33 == 1);
	}
	bool mat3_single_value_constructor_test() {
		Hexxy::Math::Matrix::Mat3 mat(2);
		return (mat.x11 == 2 && mat.x12 == 2 && mat.x13 == 2 &&
				mat.x21 == 2 && mat.x22 == 2 && mat.x23 == 2 &&
				mat.x31 == 2 && mat.x32 == 2 && mat.x33 == 2);
	}
	bool mat3_multiple_value_constructor_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		return (mat.x11 == 1 && mat.x12 == 2 && mat.x13 == 3 &&
				mat.x21 == 4 && mat.x22 == 5 && mat.x23 == 6 &&
				mat.x31 == 7 && mat.x32 == 8 && mat.x33 == 9);
	}
	bool mat3_assignement_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		Hexxy::Math::Matrix::Mat3 mat2(10,11,12,13,14,15,16,17,18);
		mat2 = mat;
		mat = Hexxy::Math::Matrix::Mat3(19,20,21,22,23,24,25,26,27);
		return (mat.x11 == 19 && mat.x12 == 20 && mat.x13 == 21 &&
				mat.x21 == 22 && mat.x22 == 23 && mat.x23 == 24 &&
				mat.x31 == 25 && mat.x32 == 26 && mat.x33 == 27 &&
				mat2.x11 == 1 && mat2.x12 == 2 && mat2.x13 == 3 &&
				mat2.x21 == 4 && mat2.x22 == 5 && mat2.x23 == 6 &&
				mat2.x31 == 7 && mat2.x32 == 8 && mat2.x33 == 9);
	}
	bool mat3_increment_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		Hexxy::Math::Matrix::Mat3 mat2 = ++mat;
		Hexxy::Math::Matrix::Mat3 mat3 = mat++;
		return (mat.x11 == 3 && mat.x12 == 4 && mat.x13 == 5 &&
				mat.x21 == 6 && mat.x22 == 7 && mat.x23 == 8 &&
				mat.x31 == 9 && mat.x32 == 10 && mat.x33 == 11 &&
				mat2.x11 == 2 && mat2.x12 == 3 && mat2.x13 == 4 &&
				mat2.x21 == 5 && mat2.x22 == 6 && mat2.x23 == 7 &&
				mat2.x31 == 8 && mat2.x32 == 9 && mat2.x33 == 10 &&
				mat3.x11 == 2 && mat3.x12 == 3 && mat3.x13 == 4 &&
				mat3.x21 == 5 && mat3.x22 == 6 && mat3.x23 == 7 &&
				mat3.x31 == 8 && mat3.x32 == 9 && mat3.x33 == 10);
	}
	bool mat3_decrement_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		Hexxy::Math::Matrix::Mat3 mat2 = --mat;
		Hexxy::Math::Matrix::Mat3 mat3 = mat--;
		return (mat.x11 == -1 && mat.x12 == 0 && mat.x13 == 1 &&
				mat.x21 == 2 && mat.x22 == 3 && mat.x23 == 4 &&
				mat.x31 == 5 && mat.x32 == 6 && mat.x33 == 7 &&
				mat2.x11 == 0 && mat2.x12 == 1 && mat2.x13 == 2 &&
				mat2.x21 == 3 && mat2.x22 == 4 && mat2.x23 == 5 &&
				mat2.x31 == 6 && mat2.x32 == 7 && mat2.x33 == 8 &&
				mat3.x11 == 0 && mat3.x12 == 1 && mat3.x13 == 2 &&
				mat3.x21 == 3 && mat3.x22 == 4 && mat3.x23 == 5 &&
				mat3.x31 == 6 && mat3.x32 == 7 && mat3.x33 == 8);
	}
	bool mat3_addition_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		mat += Hexxy::Math::Matrix::Mat3(10,11,12,13,14,15,16,17,18);
		mat += mat;
		mat = mat + mat + mat + Hexxy::Math::Matrix::Mat3(19,20,21,22,23,24,25,26,27);
		return (mat.x11 == 85 && mat.x12 == 98 && mat.x13 == 111 &&
				mat.x21 == 124 && mat.x22 == 137 && mat.x23 == 150 &&
				mat.x31 == 163 && mat.x32 == 176 && mat.x33 == 189);
	}
	bool mat3_subtraction_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		mat -= Hexxy::Math::Matrix::Mat3(10,11,12,13,14,15,16,17,18);
		mat -= mat;
		Hexxy::Math::Matrix::Mat3 mat2(19,20,21,22,23,24,25,26,27);
		mat2 = mat2 - mat2 - mat2 - Hexxy::Math::Matrix::Mat3(3);
		return (mat.x11 == 0 && mat.x12 == 0 && mat.x13 == 0 &&
				mat.x21 == 0 && mat.x22 == 0 && mat.x23 == 0 &&
				mat.x31 == 0 && mat.x32 == 0 && mat.x33 == 0 &&
				mat2.x11 == -22 && mat2.x12 == -23 && mat2.x13 == -24 &&
				mat2.x21 == -25 && mat2.x22 == -26 && mat2.x23 == -27 &&
				mat2.x31 == -28 && mat2.x32 == -29 && mat2.x33 == -30);
	}
	bool mat3_scalar_multiplication_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		mat *= 2;
		mat = mat * 3;
		return (mat.x11 == 6 && mat.x12 == 12 && mat.x13 == 18 &&
				mat.x21 == 24 && mat.x22 == 30 && mat.x23 == 36 &&
				mat.x31 == 42 && mat.x32 == 48 && mat.x33 == 54);
	}
	bool mat3_mat3_multiplication_test() {
		Hexxy::Math::Matrix::Mat3 mat(1,2,3,4,5,6,7,8,9);
		Hexxy::Math::Matrix::Mat3 mat2(10,11,12,13,14,15,16,17,18);
		mat *= mat;
		mat = mat * mat2;
		return (mat.x11 == 1440 && mat.x12 == 1548 && mat.x13 == 1656 &&
				mat.x21 == 3249 && mat.x22 == 3492 && mat.x23 == 3735 &&
				mat.x31 == 5058 && mat.x32 == 5436 && mat.x33 == 5814);
	}
	bool mat3_vec3_multiplication_test() {
		Hexxy::Math::Matrix::Mat3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
		Hexxy::Math::Vectors::Vec3 vec(10, 11, 12);
		Hexxy::Math::Vectors::Vec3 vec2 = Hexxy::Math::Vectors::Vec3::unit();
		vec2 = mat * vec;
		return (vec2.x == 68 && vec2.y == 167 && vec2.z == 266);
	}
	bool mat3_scalar_division_test() {
		Hexxy::Math::Matrix::Mat3 mat(6,12,18,24,30,36,42,48,54);
		mat /= 2;
		mat = mat / 3;
		return (mat.x11 == 1 && mat.x12 == 2 && mat.x13 == 3 &&
				mat.x21 == 4 && mat.x22 == 5 && mat.x23 == 6 &&
				mat.x31 == 7 && mat.x32 == 8 && mat.x33 == 9);
	}
	bool mat3_determinant_test() {
		Hexxy::Math::Matrix::Mat3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
		auto det = Hexxy::Math::Matrix::CalculateDeterminant(mat);
		Hexxy::Math::Matrix::Mat3 mat2(4, 2, 4, 2, 5, 2, 4, 2, 6);
		auto det2 = Hexxy::Math::Matrix::CalculateDeterminant(mat2);
		return (det == 0 && det2 == 32);
	}
	bool Tests::Hexxy_Tests_Mat3() {
		HEXXY_TEST_START;
		HEXXY_TEST(mat3_size_test);
		HEXXY_TEST(mat3_identity_matrix_test);
		HEXXY_TEST(mat3_single_value_constructor_test);
		HEXXY_TEST(mat3_multiple_value_constructor_test);
		HEXXY_TEST(mat3_assignement_test);
		HEXXY_TEST(mat3_increment_test);
		HEXXY_TEST(mat3_decrement_test);
		HEXXY_TEST(mat3_addition_test);
		HEXXY_TEST(mat3_subtraction_test);
		HEXXY_TEST(mat3_scalar_multiplication_test);
		HEXXY_TEST(mat3_mat3_multiplication_test);
		HEXXY_TEST(mat3_vec3_multiplication_test);
		HEXXY_TEST(mat3_scalar_division_test);
		HEXXY_TEST(mat3_determinant_test);
		HEXXY_TEST_END;
	}
}