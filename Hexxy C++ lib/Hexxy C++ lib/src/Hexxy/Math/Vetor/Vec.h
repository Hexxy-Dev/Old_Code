#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

namespace Hexxy { namespace Math { namespace Vectors {

	template<size_t S, typename T>
	struct Vec { };



	template<typename T>
	struct Vec<3, T> {
		union { union { struct {
		T x, y, z; };struct {
		T r, g, b; };};
		T data[3]; };

		Vec() :data() {}

		explicit Vec(T v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
		}

		Vec(T v1, T v2, T v3) {
			data[0] = v1;
			data[1] = v2;
			data[2] = v3;
		}

		Vec<3, T> operator+(const Vec<3, T>& other) const {
			Vec<3, T> v;
			v.data[0] = this->data[0] + other.data[0];
			v.data[1] = this->data[1] + other.data[1];
			v.data[2] = this->data[2] + other.data[2];
			return v;
		}
		Vec<3, T> operator-(const Vec<3, T>& other) const {
			Vec<3, T> v;
			v.data[0] = this->data[0] - other.data[0];
			v.data[1] = this->data[1] - other.data[1];
			v.data[2] = this->data[2] - other.data[2];
			return v;
		}
		Vec<3, T> operator*(T scalar) const {
			Vec<3, T> v;
			v.data[0] = this->data[0] * scalar;
			v.data[1] = this->data[1] * scalar;
			v.data[2] = this->data[2] * scalar;
			return v;
		}
		Vec<3, T> operator/(T scalar) const {
			Vec<3, T> v;
			v.data[0] = this->data[0] / scalar;
			v.data[1] = this->data[1] / scalar;
			v.data[2] = this->data[2] / scalar;
			return v;
		}

		void operator+=(const Vec<3, T>& other) {
			this->data[0] += other.data[0];
			this->data[1] += other.data[1];
			this->data[2] += other.data[2];
		}
		void operator-=(const Vec<3, T>& other) {
			this->data[0] -= other.data[0];
			this->data[1] -= other.data[1];
			this->data[2] -= other.data[2];
		}
		void operator*=(T scalar) {
			this->data[0] *= scalar;
			this->data[1] *= scalar;
			this->data[2] *= scalar;
		}
		void operator/=(T scalar) {
			this->data[0] /= scalar;
			this->data[1] /= scalar;
			this->data[2] /= scalar;
		}

		Vec<3, T>& operator++() {
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			return *this;
		}
		Vec<3, T> operator++(int) {
			Vec<3, T> old = *this;
			operator++();
			return old;
		}
		Vec<3, T>& operator--() {
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			return *this;
		}
		Vec<3, T> operator--(int) {
			Vec<3, T> old = *this;
			operator--();
			return old;
		}

		static Vec<3, T> unit() { return Vec < 3, T>(1); }

		float dot(const Vec<3, T>& other) const {
			return this->data[0] * other.data[0]
				+ this->data[1] * other.data[1]
				+ this->data[2] * other.data[2];
		}

		Vec<3, T> cross(const Vec<3, T>& other) const {
			Vec<3, T> v;
			v.data[0] = this->data[1] * other.data[2] - this->data[2] * other.data[1];
			v.data[1] = this->data[2] * other.data[0] - this->data[0] * other.data[2];
			v.data[2] = this->data[0] * other.data[1] - this->data[1] * other.data[0];
			return v;
		}

		float length() const { return sqrt(dot(*this)); }

		Vec<3, T> normalize() const {
			Vec<3, T> v;
			v.data[0] = this->data[0] / length();
			v.data[1] = this->data[1] / length();
			v.data[2] = this->data[2] / length();
			return v;
		}

		static const size_t VEC_SIZE() { return 3; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() { printf("Vec3: %d, %d, %d\n", data[0], data[1], data[2]); }
		template<> void _print<float>() { printf("Vec3: %f, %f, %f\n", data[0], data[1], data[2]); }


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Vec<3, T>& v);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Vec<3, T>& v);
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const Vec<3, T>& v) {
		stream << "Vec3: " << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << '\n';
		return stream;
	}
	template<typename T>
	std::istream& operator>>(std::istream& stream, Vec<3, T>& v) {
		stream >> v.data[0] >> v.data[1] >> v.data[2];
		return stream;
	}

	typedef Vec<3, float> Vec3;
	typedef Vec<3, uint8_t> RGB_Color;













	template<typename T>
	struct Vec<2, T> {
		union { union { struct {
		T x, y;};struct {
		T r, t;};};
		T data[2];};

		Vec() :data() {}

		explicit Vec(T v) {
			data[0] = v;
			data[1] = v;
		}

		Vec(T v1, T v2) {
			data[0] = v1;
			data[1] = v2;
		}

		Vec<2, T> operator+(const Vec<2, T>& other) const {
			Vec<2, T> v;
			v.data[0] = this->data[0] + other.data[0];
			v.data[1] = this->data[1] + other.data[1];
			return v;
		}
		Vec<2, T> operator-(const Vec<2, T>& other) const {
			Vec<2, T> v;
			v.data[0] = this->data[0] - other.data[0];
			v.data[1] = this->data[1] - other.data[1];
			return v;
		}
		Vec<2, T> operator*(T scalar) const {
			Vec<2, T> v;
			v.data[0] = this->data[0] * scalar;
			v.data[1] = this->data[1] * scalar;
			return v;
		}
		Vec<2, T> operator/(T scalar) const {
			Vec<2, T> v;
			v.data[0] = this->data[0] / scalar;
			v.data[1] = this->data[1] / scalar;
			return v;
		}

		void operator+=(const Vec<2, T>& other) {
			this->data[0] += other.data[0];
			this->data[1] += other.data[1];
		}
		void operator-=(const Vec<2, T>& other) {
			this->data[0] -= other.data[0];
			this->data[1] -= other.data[1];
		}
		void operator*=(T scalar) {
			this->data[0] *= scalar;
			this->data[1] *= scalar;
		}
		void operator/=(T scalar) {
			this->data[0] /= scalar;
			this->data[1] /= scalar;
		}

		Vec<2, T>& operator++() {
			this->data[0]++;
			this->data[1]++;
			return *this;
		}
		Vec<2, T> operator++(int) {
			Vec<2, T> old = *this;
			operator++();
			return old;
		}
		Vec<2, T>& operator--() {
			this->data[0]--;
			this->data[1]--;
			return *this;
		}
		Vec<2, T> operator--(int) {
			Vec<2, T> old = *this;
			operator--();
			return old;
		}

		static Vec<2, T> unit() { return Vec < 2, T>(1); }

		float dot(const Vec<2, T>& other) const {
			return this->data[0] * other.data[0]
				+ this->data[1] * other.data[1];
		}

		float length() const { return sqrt(dot(*this)); }

		Vec<2, T> normalize() const {
			Vec<2, T> v;
			v.data[0] = this->data[0] / length();
			v.data[1] = this->data[1] / length();
			return v;
		}

		float angle() const { return std::atan2f(data[0], data[1]); }
		float angle_degrees() const { return angle() * 180 / M_PI; }

		static const size_t VEC_SIZE() { return 2; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() { printf("Vec2: %d, %d\n", data[0], data[1]); }
		template<> void _print<float>() { printf("Vec2: %f, %f\n", data[0], data[1]); }


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Vec<2, T>& v);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Vec<2, T>& v);
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const Vec<2, T>& v) {
		stream << "Vec2: " << v.data[0] << ", " << v.data[1] << '\n';
		return stream;
	}
	template<typename T>
	std::istream& operator>>(std::istream& stream, Vec<2, T>& v) {
		stream >> v.data[0] >> v.data[1];
		return stream;
	}

	typedef Vec<2, float> Vec2;














	template<typename T>
	struct Vec<4, T> {
		union { union { struct {
		T x, y, z, w; };struct {
		T r, g, b, a; };};
		T data[4]; };

		Vec() :data() {}

		explicit Vec(T v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
			data[3] = v;
		}

		Vec(T v1, T v2, T v3, T v4) {
			data[0] = v1;
			data[1] = v2;
			data[2] = v3;
			data[3] = v4;
		}

		Vec<4, T> operator+(const Vec<4, T>& other) const {
			Vec<4, T> v;
			v.data[0] = this->data[0] + other.data[0];
			v.data[1] = this->data[1] + other.data[1];
			v.data[2] = this->data[2] + other.data[2];
			v.data[3] = this->data[3] + other.data[3];
			return v;
		}
		Vec<4, T> operator-(const Vec<4, T>& other) const {
			Vec<4, T> v;
			v.data[0] = this->data[0] - other.data[0];
			v.data[1] = this->data[1] - other.data[1];
			v.data[2] = this->data[2] - other.data[2];
			v.data[3] = this->data[3] - other.data[3];
			return v;
		}
		Vec<4, T> operator*(T scalar) const {
			Vec<4, T> v;
			v.data[0] = this->data[0] * scalar;
			v.data[1] = this->data[1] * scalar;
			v.data[2] = this->data[2] * scalar;
			v.data[3] = this->data[3] * scalar;
			return v;
		}
		Vec<4, T> operator/(T scalar) const {
			Vec<4, T> v;
			v.data[0] = this->data[0] / scalar;
			v.data[1] = this->data[1] / scalar;
			v.data[2] = this->data[2] / scalar;
			v.data[3] = this->data[3] / scalar;
			return v;
		}

		void operator+=(const Vec<4, T>& other) {
			this->data[0] += other.data[0];
			this->data[1] += other.data[1];
			this->data[2] += other.data[2];
			this->data[3] += other.data[3];
		}
		void operator-=(const Vec<4, T>& other) {
			this->data[0] -= other.data[0];
			this->data[1] -= other.data[1];
			this->data[2] -= other.data[2];
			this->data[3] -= other.data[3];
		}
		void operator*=(T scalar) {
			this->data[0] *= scalar;
			this->data[1] *= scalar;
			this->data[2] *= scalar;
			this->data[3] *= scalar;
		}
		void operator/=(T scalar) {
			this->data[0] /= scalar;
			this->data[1] /= scalar;
			this->data[2] /= scalar;
			this->data[3] /= scalar;
		}

		Vec<4, T>& operator++() {
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			this->data[3]++;
			return *this;
		}
		Vec<4, T> operator++(int) {
			Vec<4, T> old = *this;
			operator++();
			return old;
		}
		Vec<4, T>& operator--() {
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			this->data[3]--;
			return *this;
		}
		Vec<4, T> operator--(int) {
			Vec<4, T> old = *this;
			operator--();
			return old;
		}

		static Vec<4, T> unit() { return Vec<4, T>(1); }

		float dot(const Vec<4, T>& other) const {
			return this->data[0] * other.data[0]
				+ this->data[1] * other.data[1]
				+ this->data[2] * other.data[2]
				+ this->data[3] * other.data[3];
		}

		float length() const { return sqrt(dot(*this)); }

		Vec<4, T> normalize() const {
			Vec<4, T> v;
			v.data[0] = this->data[0] / length();
			v.data[1] = this->data[1] / length();
			v.data[2] = this->data[2] / length();
			v.data[3] = this->data[3] / length();
			return v;
		}

		static const size_t VEC_SIZE() { return 4; }

		void print() { _print<T>(); }
		template<typename S> void _print() {}
		template<> void _print<uint8_t>() { printf("Vec4: %d, %d, %d, %d\n", data[0], data[1], data[2], data[3]); }
		template<> void _print<float>() { printf("Vec4: %f, %f, %f, %f\n", data[0], data[1], data[2], data[3]); }


		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Vec<4, T>& v);
		template<typename T>
		friend std::istream& operator>>(std::istream& stream, Vec<4, T>& v);
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const Vec<4, T>& v) {
		stream << "Vec4: " << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ", " << v.data[3] << '\n';
		return stream;
	}
	template<typename T>
	std::istream& operator>>(std::istream& stream, Vec<4, T>& v) {
		stream >> v.data[0] >> v.data[1] >> v.data[2] >> v.data[3];
		return stream;
	}

	typedef Vec<4, float> Vec4;
	typedef Vec<4, uint8_t> RGBA_Color;

} } }