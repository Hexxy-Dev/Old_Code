#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "../Vetor/Vec.h"

namespace Hexxy { namespace Math { namespace Matrix {

	enum Major_Ordering {
		Row_Major,
		Column_Major
	};

	template<size_t R, size_t C, typename T, Major_Ordering O>
	struct Mat { };

	template<typename T, Major_Ordering O>
	struct Mat<2, 2, T, O> {
		union { struct {
		float x11, x12;
		float x21, x22;};
		float data[2 * 2];};

		Mat() :data() {}

		explicit Mat(float x)
		{
			for (uint8_t i = 0; i < 2 * 2; i++)
				data[i] = x;
		}

		Mat(float x11, float x12, float x21, float x22)
		{
			data[0] = x11;
			data[1] = x12;
			data[2] = x21;
			data[3] = x22;
		}

		Mat<2, 2, T, O> operator+(const Mat<2, 2, T, O>& other) const {
			Mat<2, 2, T, O> m;
			for (uint8_t i = 0; i < 2 * 2; i++)
				m.data[i] = this->data[i] + other.data[i];
			return m;
		}
		Mat<2, 2, T, O> operator-(const Mat<2, 2, T, O>& other) const {
			Mat<2, 2, T, O> m;
			for (uint8_t i = 0; i < 2 * 2; i++)
				m.data[i] = this->data[i] - other.data[i];
			return m;
		}
		Mat<2, 2, T, O> operator*(T scalar) const {
			Mat<2, 2, T, O> m;
			for (uint8_t i = 0; i < 2 * 2; i++)
				m.data[i] = this->data[i] * scalar;
			return m;
		}

		Mat<2, 2, T, O> operator*(const Mat<2, 2, T, O>& other) { return Mat2_Multiplication<O>(other); }
		Hexxy::Math::Vectors::Vec<2, T> operator*(const Hexxy::Math::Vectors::Vec<2, T>& other)
		{ return Vec2_Multiplication<O>(other); }
		template<Major_Ordering O>
		Mat<2, 2, T, O> Mat2_Multiplication(const Mat<2, 2, T, O>& other);
		template<>
		Mat<2, 2, T, O> Mat2_Multiplication<Row_Major>(const Mat<2, 2, T, O>& other){
			Mat<2, 2, T, O> m;
			m.x11 = this->x11 * other.x11 + this->x12 * other.x21;
			m.x12 = this->x11 * other.x12 + this->x12 * other.x22;
			m.x21 = this->x21 * other.x11 + this->x22 * other.x21;
			m.x22 = this->x21 * other.x12 + this->x22 * other.x22;
			return m;
		}
		template<Major_Ordering O>
		Hexxy::Math::Vectors::Vec<2, T> Vec2_Multiplication(const Hexxy::Math::Vectors::Vec<2, T>& other);
		template<>
		Hexxy::Math::Vectors::Vec<2, T> Vec2_Multiplication<Row_Major>(const Hexxy::Math::Vectors::Vec<2, T>& other){
			Hexxy::Math::Vectors::Vec<2, T> v;
			v.x = this->x11 * other.x + this->x12 * other.y;
			v.y = this->x21 * other.x + this->x22 * other.y;
			return v;
		}

		Mat<2, 2, T, O> operator/(T scalar) const {
			Mat<2, 2, T, O> m;
			for (uint8_t i = 0; i < 2 * 2; i++)
				m.data[i] = this->data[i] / scalar;
			return m;
		}

		void operator+=(const Mat<2, 2, T, O>& other) {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i] += other.data[i];
		}
		void operator-=(const Mat<2, 2, T, O>& other) {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i] -= other.data[i];
		}
		void operator*=(T scalar) {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i] *= scalar;
		}

		void operator*=(const Mat<2, 2, T, O> other) { Mat2_Self_Multiplication(other); }

		template<Major_Ordering O> void Mat2_Self_Multiplication(const Mat<2, 2, T, O> other);
		template<>
		void Mat2_Self_Multiplication<Row_Major>(const Mat<2, 2, T, O> other) {
			Mat<2, 2, T, O> old = *this;
			this->x11 = old.x11 * other.x11 + old.x12 * other.x21;
			this->x12 = old.x11 * other.x12 + old.x12 * other.x22;
			this->x21 = old.x21 * other.x11 + old.x22 * other.x21;
			this->x22 = old.x21 * other.x12 + old.x22 * other.x22;
		}


		void operator/=(T scalar) {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i] /= scalar;
		}

		Mat<2, 2, T, O>& operator++() {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i]++;
			return *this;
		}
		Mat<2, 2, T, O> operator++(int) {
			Mat<2, 2, T, O> old = *this;
			operator++();
			return old;
		}
		Mat<2, 2, T, O>& operator--() {
			for (uint8_t i = 0; i < 2 * 2; i++)
				this->data[i]--;
			return *this;
		}
		Mat<2, 2, T, O> operator--(int) {
			Mat<2, 2, T, O> old = *this;
			operator--();
			return old;
		}

		static Mat<2, 2, T, O> identity() { return Mat< 2, 2, T, O>(1); }

		static const size_t MAT_R_SIZE() { return 2; }
		static const size_t MAT_C_SIZE() { return 2; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() { printf("Mat2x2:\n%d, %d\n%d, %d\n", data[0], data[1], data[2], data[3]); }
		template<> void _print<float>() { printf("Mat2x2:\n%f, %f\n%f, %f\n", data[0], data[1], data[2], data[3]); }


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Mat<2, 2, T, O>& m);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Mat<2, 2, T, O>& m);
	};
	template<typename T, Major_Ordering O>
	std::ostream& operator<<(std::ostream& stream, const Mat<2, 2, T, O>& m) {
		stream << "Mat2x2:\n" << m.data[0] << ", " << m.data[1] << '\n' << m.data[2] << ", " << m.data[3] << '\n';
		return stream;
	}
	template<typename T, Major_Ordering O>
	std::istream& operator>>(std::istream& stream, Mat<2, 2, T, O>& m) {
		stream >> m.data[0] >> m.data[1] >> m.data[2] >> m.data[3];
		return stream;
	}

	typedef Mat<2, 2, float, Row_Major> Mat2;









	template<typename T, Major_Ordering O>
	struct Mat<3, 3, T, O> {
		union {
			struct {
				float x11, x12, x13;
				float x21, x22, x23;
				float x31, x32, x33;
			};
			float data[3 * 3];
		};

		Mat() :data() {}

		explicit Mat(float x)
		{
			for (uint8_t i = 0; i < 3 * 3; i++)
				data[i] = x;
		}

		Mat(float x11, float x12, float x13, float x21, float x22, float x23, float x31, float x32, float x33)
		{
			data[0] = x11;
			data[1] = x12;
			data[2] = x13;
			data[3] = x21;
			data[4] = x22;
			data[5] = x23;
			data[6] = x31;
			data[7] = x32;
			data[8] = x33;
		}

		Mat<3, 3, T, O> operator+(const Mat<3, 3, T, O>& other) const {
			Mat<3, 3, T, O> m;
			for (uint8_t i = 0; i < 3 * 3; i++)
				m.data[i] = this->data[i] + other.data[i];
			return m;
		}
		Mat<3, 3, T, O> operator-(const Mat<3, 3, T, O>& other) const {
			Mat<3, 3, T, O> m;
			for (uint8_t i = 0; i < 3 * 3; i++)
				m.data[i] = this->data[i] - other.data[i];
			return m;
		}
		Mat<3, 3, T, O> operator*(T scalar) const {
			Mat<3, 3, T, O> m;
			for (uint8_t i = 0; i < 3 * 3; i++)
				m.data[i] = this->data[i] * scalar;
			return m;
		}

		Mat<3, 3, T, O> operator*(const Mat<3, 3, T, O>& other) { return Mat3_Multiplication<O>(other); }
		Hexxy::Math::Vectors::Vec<3, T> operator*(const Hexxy::Math::Vectors::Vec<3, T>& other)
		{ return Vec3_Multiplication<O>(other); }
		template<Major_Ordering O>
		Mat<3, 3, T, O> Mat3_Multiplication(const Mat<3, 3, T, O>& other);
		template<>
		Mat<3, 3, T, O> Mat3_Multiplication<Row_Major>(const Mat<3, 3, T, O>& other) {
			Mat<3, 3, T, O> m;
			m.x11 = this->x11 * other.x11 + this->x12 * other.x21 + this->x13 * other.x31;
			m.x12 = this->x11 * other.x12 + this->x12 * other.x22 + this->x13 * other.x32;
			m.x13 = this->x11 * other.x13 + this->x12 * other.x23 + this->x13 * other.x33;

			m.x21 = this->x21 * other.x11 + this->x22 * other.x21 + this->x23 * other.x31;
			m.x22 = this->x21 * other.x12 + this->x22 * other.x22 + this->x23 * other.x32;
			m.x23 = this->x21 * other.x13 + this->x22 * other.x23 + this->x23 * other.x33;

			m.x31 = this->x31 * other.x11 + this->x32 * other.x21 + this->x33 * other.x31;
			m.x32 = this->x31 * other.x12 + this->x32 * other.x22 + this->x33 * other.x32;
			m.x33 = this->x31 * other.x13 + this->x32 * other.x23 + this->x33 * other.x33;
			return m;
		}

		template<Major_Ordering O>
		Hexxy::Math::Vectors::Vec<3, T> Vec3_Multiplication(const Hexxy::Math::Vectors::Vec<3, T>& other);
		template<>
		Hexxy::Math::Vectors::Vec<3, T> Vec3_Multiplication<Row_Major>(const Hexxy::Math::Vectors::Vec<3, T>& other) {
			Hexxy::Math::Vectors::Vec<3, T> v;
			v.x = this->x11 * other.x + this->x12 * other.y + this->x13 * other.z;
			v.y = this->x21 * other.x + this->x22 * other.y + this->x23 * other.z;
			v.z = this->x31 * other.x + this->x32 * other.y + this->x33 * other.z;
			return v;
		}

		Mat<3, 3, T, O> operator/(T scalar) const {
			Mat<3, 3, T, O> m;
			for (uint8_t i = 0; i < 3 * 3; i++)
				m.data[i] = this->data[i] / scalar;
			return m;
		}

		void operator+=(const Mat<3, 3, T, O>& other) {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i] += other.data[i];
		}
		void operator-=(const Mat<3, 3, T, O>& other) {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i] -= other.data[i];
		}
		void operator*=(T scalar) {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i] *= scalar;
		}

		void operator*=(const Mat<3, 3, T, O> other) { Mat3_Self_Multiplication(other); }

		template<Major_Ordering O> void Mat3_Self_Multiplication(const Mat<3, 3, T, O> other);
		template<>
		void Mat3_Self_Multiplication<Row_Major>(const Mat<3, 3, T, O> other) {
			Mat<3, 3, T, O> old = *this;
			this->x11 = old.x11 * other.x11 + old.x12 * other.x21 + old.x13 * other.x31;
			this->x12 = old.x11 * other.x12 + old.x12 * other.x22 + old.x13 * other.x32;
			this->x13 = old.x11 * other.x13 + old.x12 * other.x23 + old.x13 * other.x33;

			this->x21 = old.x21 * other.x11 + old.x22 * other.x21 + old.x23 * other.x31;
			this->x22 = old.x21 * other.x12 + old.x22 * other.x22 + old.x23 * other.x32;
			this->x23 = old.x21 * other.x13 + old.x22 * other.x23 + old.x23 * other.x33;

			this->x31 = old.x31 * other.x11 + old.x32 * other.x21 + old.x33 * other.x31;
			this->x32 = old.x31 * other.x12 + old.x32 * other.x22 + old.x33 * other.x32;
			this->x33 = old.x31 * other.x13 + old.x32 * other.x23 + old.x33 * other.x33;
		}


		void operator/=(T scalar) {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i] /= scalar;
		}

		Mat<3, 3, T, O>& operator++() {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i]++;
			return *this;
		}
		Mat<3, 3, T, O> operator++(int) {
			Mat<3, 3, T, O> old = *this;
			operator++();
			return old;
		}
		Mat<3, 3, T, O>& operator--() {
			for (uint8_t i = 0; i < 3 * 3; i++)
				this->data[i]--;
			return *this;
		}
		Mat<3, 3, T, O> operator--(int) {
			Mat<3, 3, T, O> old = *this;
			operator--();
			return old;
		}

		static Mat<3, 3, T, O> identity() { return Mat<3, 3, T, O>(1); }

		static const size_t MAT_R_SIZE() { return 3; }
		static const size_t MAT_C_SIZE() { return 3; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() { printf("Mat3x3:\n%d, %d, %d\n%d, %d, %d\n%d, %d, %d\n",
			data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]); }
		template<> void _print<float>() { printf("Mat3x3:\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n",
			data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]); }


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Mat<3, 3, T, O>& m);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Mat<3, 3, T, O>& m);
	};
	template<typename T, Major_Ordering O>
	std::ostream& operator<<(std::ostream& stream, const Mat<3, 3, T, O>& m) {
		stream << "Mat3x3:\n"
			<< m.data[0] << ", " << m.data[1] << ", " << m.data[2] << '\n'
			<< m.data[3] << ", " << m.data[4] << ", " << m.data[5] << '\n'
			<< m.data[6] << ", " << m.data[7] << ", " << m.data[8] << '\n';
		return stream;
	}
	template<typename T, Major_Ordering O>
	std::istream& operator>>(std::istream& stream, Mat<3, 3, T, O>& m) {
		stream >> m.data[0] >> m.data[1] >> m.data[2]
			>> m.data[3] >> m.data[4] >> m.data[5]
			>> m.data[6] >> m.data[7] >> m.data[8];
		return stream;
	}

	typedef Mat<3, 3, float, Row_Major> Mat3;










	template<typename T, Major_Ordering O>
	struct Mat<4, 4, T, O> {
		union {
			struct {
				float x11, x12, x13, x14;
				float x21, x22, x23, x24;
				float x31, x32, x33, x34;
				float x41, x42, x43, x44;
			};
			float data[4 * 4];
		};

		Mat() :data() {}

		explicit Mat(float x)
		{
			for (uint8_t i = 0; i < 4 * 4; i++)
				data[i] = x;
		}

		Mat(float x11, float x12, float x13, float x14, float x21, float x22, float x23, float x24, float x31, float x32, float x33, float x34, float x41, float x42, float x43, float x44)
		{
			data[0] = x11;
			data[1] = x12;
			data[2] = x13;
			data[3] = x14;
			data[4] = x21;
			data[5] = x22;
			data[6] = x23;
			data[7] = x24;
			data[8] = x31;
			data[9] = x32;
			data[10] = x33;
			data[11] = x34;
			data[12] = x41;
			data[13] = x42;
			data[14] = x43;
			data[15] = x44;
		}

		Mat<4, 4, T, O> operator+(const Mat<4, 4, T, O>& other) const {
			Mat<4, 4, T, O> m;
			for (uint8_t i = 0; i < 4 * 4; i++)
				m.data[i] = this->data[i] + other.data[i];
			return m;
		}
		Mat<4, 4, T, O> operator-(const Mat<4, 4, T, O>& other) const {
			Mat<4, 4, T, O> m;
			for (uint8_t i = 0; i < 4 * 4; i++)
				m.data[i] = this->data[i] - other.data[i];
			return m;
		}
		Mat<4, 4, T, O> operator*(T scalar) const {
			Mat<4, 4, T, O> m;
			for (uint8_t i = 0; i < 4 * 4; i++)
				m.data[i] = this->data[i] * scalar;
			return m;
		}

		Mat<4, 4, T, O> operator*(const Mat<4, 4, T, O>& other) { return Mat4_Multiplication<O>(other); }
		Hexxy::Math::Vectors::Vec<4, T> operator*(const Hexxy::Math::Vectors::Vec<4, T>& other)
		{ return Vec4_Multiplication<O>(other); }
		template<Major_Ordering O>
		Mat<4, 4, T, O> Mat4_Multiplication(const Mat<4, 4, T, O>& other);
		template<>
		Mat<4, 4, T, O> Mat4_Multiplication<Row_Major>(const Mat<4, 4, T, O>& other) {
			Mat<4, 4, T, O> m;
			m.x11 = this->x11 * other.x11 + this->x12 * other.x21 + this->x13 * other.x31 + this->x14 * other.x41;
			m.x12 = this->x11 * other.x12 + this->x12 * other.x22 + this->x13 * other.x32 + this->x14 * other.x42;
			m.x13 = this->x11 * other.x13 + this->x12 * other.x23 + this->x13 * other.x33 + this->x14 * other.x43;
			m.x14 = this->x11 * other.x14 + this->x12 * other.x24 + this->x13 * other.x34 + this->x14 * other.x44;

			m.x21 = this->x21 * other.x11 + this->x22 * other.x21 + this->x23 * other.x31 + this->x24 * other.x41;
			m.x22 = this->x21 * other.x12 + this->x22 * other.x22 + this->x23 * other.x32 + this->x24 * other.x42;
			m.x23 = this->x21 * other.x13 + this->x22 * other.x23 + this->x23 * other.x33 + this->x24 * other.x43;
			m.x24 = this->x21 * other.x14 + this->x22 * other.x24 + this->x23 * other.x34 + this->x24 * other.x44;

			m.x31 = this->x31 * other.x11 + this->x32 * other.x21 + this->x33 * other.x31 + this->x34 * other.x41;
			m.x32 = this->x31 * other.x12 + this->x32 * other.x22 + this->x33 * other.x32 + this->x34 * other.x42;
			m.x33 = this->x31 * other.x13 + this->x32 * other.x23 + this->x33 * other.x33 + this->x34 * other.x43;
			m.x34 = this->x31 * other.x14 + this->x32 * other.x24 + this->x33 * other.x34 + this->x34 * other.x44;

			m.x41 = this->x41 * other.x11 + this->x42 * other.x21 + this->x43 * other.x31 + this->x44 * other.x41;
			m.x42 = this->x41 * other.x12 + this->x42 * other.x22 + this->x43 * other.x32 + this->x44 * other.x42;
			m.x43 = this->x41 * other.x13 + this->x42 * other.x23 + this->x43 * other.x33 + this->x44 * other.x43;
			m.x44 = this->x41 * other.x14 + this->x42 * other.x24 + this->x43 * other.x34 + this->x44 * other.x44;
			return m;
		}

		template<Major_Ordering O>
		Hexxy::Math::Vectors::Vec<4, T> Vec4_Multiplication(const Hexxy::Math::Vectors::Vec<4, T>& other);
		template<>
		Hexxy::Math::Vectors::Vec<4, T> Vec4_Multiplication<Row_Major>(const Hexxy::Math::Vectors::Vec<4, T>& other) {
			Hexxy::Math::Vectors::Vec<4, T> v;
			v.x = this->x11 * other.x + this->x12 * other.y + this->x13 * other.z + this->x14 * other.w;
			v.y = this->x21 * other.x + this->x22 * other.y + this->x23 * other.z + this->x24 * other.w;
			v.z = this->x31 * other.x + this->x32 * other.y + this->x33 * other.z + this->x34 * other.w;
			v.w = this->x41 * other.x + this->x42 * other.y + this->x43 * other.z + this->x44 * other.w;
			return v;
		}

		Mat<4, 4, T, O> operator/(T scalar) const {
			Mat<4, 4, T, O> m;
			for (uint8_t i = 0; i < 4 * 4; i++)
				m.data[i] = this->data[i] / scalar;
			return m;
		}

		void operator+=(const Mat<4, 4, T, O>& other) {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i] += other.data[i];
		}
		void operator-=(const Mat<4, 4, T, O>& other) {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i] -= other.data[i];
		}
		void operator*=(T scalar) {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i] *= scalar;
		}

		void operator*=(const Mat<4, 4, T, O> other) { Mat4_Self_Multiplication(other); }

		template<Major_Ordering O> void Mat4_Self_Multiplication(const Mat<4, 4, T, O> other);
		template<>
		void Mat4_Self_Multiplication<Row_Major>(const Mat<4, 4, T, O> other) {
			Mat<4, 4, T, O> old = *this;
			this->x11 = old.x11 * other.x11 + old.x12 * other.x21 + old.x13 * other.x31 + old.x14 * other.x41;
			this->x12 = old.x11 * other.x12 + old.x12 * other.x22 + old.x13 * other.x32 + old.x14 * other.x42;
			this->x13 = old.x11 * other.x13 + old.x12 * other.x23 + old.x13 * other.x33 + old.x14 * other.x43;
			this->x14 = old.x11 * other.x14 + old.x12 * other.x24 + old.x13 * other.x34 + old.x14 * other.x44;

			this->x21 = old.x21 * other.x11 + old.x22 * other.x21 + old.x23 * other.x31 + old.x24 * other.x41;
			this->x22 = old.x21 * other.x12 + old.x22 * other.x22 + old.x23 * other.x32 + old.x24 * other.x42;
			this->x23 = old.x21 * other.x13 + old.x22 * other.x23 + old.x23 * other.x33 + old.x24 * other.x43;
			this->x24 = old.x21 * other.x14 + old.x22 * other.x24 + old.x23 * other.x34 + old.x24 * other.x44;

			this->x31 = old.x31 * other.x11 + old.x32 * other.x21 + old.x33 * other.x31 + old.x34 * other.x41;
			this->x32 = old.x31 * other.x12 + old.x32 * other.x22 + old.x33 * other.x32 + old.x34 * other.x42;
			this->x33 = old.x31 * other.x13 + old.x32 * other.x23 + old.x33 * other.x33 + old.x34 * other.x43;
			this->x34 = old.x31 * other.x14 + old.x32 * other.x24 + old.x33 * other.x34 + old.x34 * other.x44;

			this->x41 = old.x41 * other.x11 + old.x42 * other.x21 + old.x43 * other.x31 + old.x44 * other.x41;
			this->x42 = old.x41 * other.x12 + old.x42 * other.x22 + old.x43 * other.x32 + old.x44 * other.x42;
			this->x43 = old.x41 * other.x13 + old.x42 * other.x23 + old.x43 * other.x33 + old.x44 * other.x43;
			this->x44 = old.x41 * other.x14 + old.x42 * other.x24 + old.x43 * other.x34 + old.x44 * other.x44;
		}


		void operator/=(T scalar) {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i] /= scalar;
		}

		Mat<4, 4, T, O>& operator++() {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i]++;
			return *this;
		}
		Mat<4, 4, T, O> operator++(int) {
			Mat<4, 4, T, O> old = *this;
			operator++();
			return old;
		}
		Mat<4, 4, T, O>& operator--() {
			for (uint8_t i = 0; i < 4 * 4; i++)
				this->data[i]--;
			return *this;
		}
		Mat<4, 4, T, O> operator--(int) {
			Mat<4, 4, T, O> old = *this;
			operator--();
			return old;
		}

		static Mat<4, 4, T, O> identity() { return Mat<4, 4, T, O>(1); }

		static const size_t MAT_R_SIZE() { return 4; }
		static const size_t MAT_C_SIZE() { return 4; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() {
			printf("Mat4x4:\n%d, %d, %d, %d\n%d, %d, %d, %d\n%d, %d, %d, %d\n%d, %d, %d, %d\n",
				data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
		}
		template<> void _print<float>() {
			printf("Mat4x4:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
				data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
		}


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Mat<4, 4, T, O>& m);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Mat<4, 4, T, O>& m);
	};
	template<typename T, Major_Ordering O>
	std::ostream& operator<<(std::ostream& stream, const Mat<4, 4, T, O>& m) {
		stream << "Mat4x4:\n"
			<< m.data[0] << ", " << m.data[1] << ", " << m.data[2] << ", " << m.data[3] << '\n'
			<< m.data[4] << ", " << m.data[5] << ", " << m.data[6] << ", " << m.data[7] << '\n'
			<< m.data[8] << ", " << m.data[9] << ", " << m.data[10] << ", " << m.data[11] << '\n'
			<< m.data[12] << ", " << m.data[13] << ", " << m.data[14] << ", " << m.data[15] << '\n';
		return stream;
	}
	template<typename T, Major_Ordering O>
	std::istream& operator>>(std::istream& stream, Mat<4, 4, T, O>& m) {
		stream >> m.data[0] >> m.data[1] >> m.data[2] >> m.data[3]
			>> m.data[4] >> m.data[5] >> m.data[6] >> m.data[7]
			>> m.data[8] >> m.data[9] >> m.data[10] >> m.data[11]
			>> m.data[12] >> m.data[13] >> m.data[14] >> m.data[15];
		return stream;
	}

	typedef Mat<4, 4, float, Row_Major> Mat4;


} } }