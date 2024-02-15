#include "Tests.hpp"

namespace Hexxy {
	bool mat2_size_test() {
		Hexxy::Math::Matrix::Mat2 mat(2);
		return (mat.MAT_R_SIZE() == 2 && mat.MAT_C_SIZE() == 2
			&& sizeof(mat) == sizeof(mat.x11) * mat.MAT_R_SIZE() * mat.MAT_C_SIZE());
	}
	bool mat2_identity_matrix_test() {
		Hexxy::Math::Matrix::Mat2 mat = Hexxy::Math::Matrix::Mat2::identity();
		return (mat.x11 == 1 && mat.x12 == 1 && mat.x21 == 1 && mat.x22 == 1);
	}
	bool mat2_single_value_constructor_test() {
		Hexxy::Math::Matrix::Mat2 mat(2);
		return (mat.x11 == 2 && mat.x12 == 2 && mat.x21 == 2 && mat.x22 == 2);
	}
	bool mat2_multiple_value_constructor_test() {
		Hexxy::Math::Matrix::Mat2 mat(2, 3, 4, 5);
		return (mat.x11 == 2 && mat.x12 == 3 && mat.x21 == 4 && mat.x22 == 5);
	}
	bool mat2_assignement_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		Hexxy::Math::Matrix::Mat2 mat2(5,6,7,8);
		mat2 = mat;
		mat = Hexxy::Math::Matrix::Mat2(5, 6, 7, 8);
		return (mat.x11 == 5 && mat.x12 == 6 && mat.x21 == 7 && mat.x22 == 8
			&& mat2.x11 == 1 && mat2.x12 == 2 && mat2.x21 == 3 && mat2.x22 == 4);
	}
	bool mat2_increment_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		Hexxy::Math::Matrix::Mat2 mat2 = ++mat;
		Hexxy::Math::Matrix::Mat2 mat3 = mat++;
		return (mat.x11 == 3 && mat.x12 == 4 && mat.x21 == 5 && mat.x22 == 6
			&& mat2.x11 == 2 && mat2.x12 == 3 && mat2.x21 == 4 && mat2.x22 == 5
			&& mat3.x11 == 2 && mat3.x12 == 3 && mat3.x21 == 4 && mat3.x22 == 5);
	}
	bool mat2_decrement_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		Hexxy::Math::Matrix::Mat2 mat2 = --mat;
		Hexxy::Math::Matrix::Mat2 mat3 = mat--;
		return (mat.x11 == -1 && mat.x12 == 0 && mat.x21 == 1 && mat.x22 == 2
			&& mat2.x11 == 0 && mat2.x12 == 1 && mat2.x21 == 2 && mat2.x22 == 3
			&& mat3.x11 == 0 && mat3.x12 == 1 && mat3.x21 == 2 && mat3.x22 == 3);
	}
	bool mat2_addition_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		mat += Hexxy::Math::Matrix::Mat2(5,6,7,8);
		mat += mat;
		mat = mat + mat + mat + Hexxy::Math::Matrix::Mat2(10,11,12,13);
		return (mat.x11 == 46 && mat.x12 == 59 && mat.x21 == 72 && mat.x22 == 85);
	}
	bool mat2_subtraction_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		mat -= Hexxy::Math::Matrix::Mat2(5,6,7,8);
		mat -= mat;
		Hexxy::Math::Matrix::Mat2 mat2(9,10,11,12);
		mat2 = mat2 - mat2 - mat2 - Hexxy::Math::Matrix::Mat2(1,2,3,4);
		return (mat.x11 == 0 && mat.x12 == 0 && mat.x21 == 0 && mat.x22 == 0
			&& mat2.x11 == -10 && mat2.x12 == -12 && mat2.x21 == -14 && mat2.x22 == -16);
	}
	bool mat2_scalar_multiplication_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		mat *= 2;
		mat = mat * 3;
		return (mat.x11 == 6 && mat.x12 == 12 && mat.x21 == 18 && mat.x22 == 24);
	}
	bool mat2_mat2_multiplication_test() {
		Hexxy::Math::Matrix::Mat2 mat(1,2,3,4);
		Hexxy::Math::Matrix::Mat2 mat2(5,6,7,8);
		mat *= mat;
		mat = mat * mat2;
		return (mat.x11 == 105 && mat.x12 == 122 && mat.x21 == 229 && mat.x22 == 266);
	}
	bool mat2_vec2_multiplication_test() {
		Hexxy::Math::Matrix::Mat2 mat(1, 2, 3, 4);
		Hexxy::Math::Vectors::Vec2 vec(5, 6);
		Hexxy::Math::Vectors::Vec2 vec2 = Hexxy::Math::Vectors::Vec2::unit();
		vec2 = mat * vec;
		return (vec2.x == 17 && vec2.y == 39 );
	}
	bool mat2_scalar_division_test() {
		Hexxy::Math::Matrix::Mat2 mat(12,24,36,48);
		mat /= 2;
		mat = mat / 3;
		return (mat.x11 == 2 && mat.x12 == 4 && mat.x21 == 6 && mat.x22 == 8);
	}
	bool mat2_determinant_test() {
		Hexxy::Math::Matrix::Mat2 mat(1, 2, 3, 4);
		auto det = Hexxy::Math::Matrix::CalculateDeterminant(mat);
		Hexxy::Math::Matrix::Mat2 mat2(4, 2, 2, 5);
		auto det2 = Hexxy::Math::Matrix::CalculateDeterminant(mat2);
		return (det == -2 && det2 == 16);
	}
	bool Tests::Hexxy_Tests_Mat2() {
		HEXXY_TEST_START;
		HEXXY_TEST(mat2_size_test);
		HEXXY_TEST(mat2_identity_matrix_test);
		HEXXY_TEST(mat2_single_value_constructor_test);
		HEXXY_TEST(mat2_multiple_value_constructor_test);
		HEXXY_TEST(mat2_assignement_test);
		HEXXY_TEST(mat2_increment_test);
		HEXXY_TEST(mat2_decrement_test);
		HEXXY_TEST(mat2_addition_test);
		HEXXY_TEST(mat2_subtraction_test);
		HEXXY_TEST(mat2_scalar_multiplication_test);
		HEXXY_TEST(mat2_mat2_multiplication_test);
		HEXXY_TEST(mat2_vec2_multiplication_test);
		HEXXY_TEST(mat2_scalar_division_test);
		HEXXY_TEST(mat2_determinant_test);
		HEXXY_TEST_END;
	}
}