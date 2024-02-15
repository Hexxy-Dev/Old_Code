#pragma once

//
// CHALLANGE DESCRIPTION:
// COMPLETE THE FOLLOWING STRUCT
// T is a SIGNED variable (char, short, int, long, long long, etc.)
// RULES:
// use only binary operations( ~ ^ & | ) on the m_value data member
// you can use an already implemented operator in another operator
// ex: in void operator+=() ... T result = this.operator+(other);   or  var.operator++();
// while and do while structures can be used
// for can also be used but ONLY with the CustomVar as iterator :)
// ONLY CustomVar local variables may be created
// the constness for every operator has already been defined do not redefine/delete it
// the private m_value member can be accessed
// you can create private functions as you see fit
// you are not allowed to overload other operators
// edge cases have to be accounted for as well
// if an edge case renders the operation impossible you should just use   throw "MESSAGE";
// do not search the solution online
// do not include other headers
//

template<typename T>
struct CustomVar {
	CustomVar() = default;
	CustomVar(const T value)
		: m_value(value)
	{}

	CustomVar operator+(const CustomVar& other) const
	{
		return 0;
	}
	CustomVar operator-(const CustomVar& other) const
	{
		return 0;
	}
	CustomVar operator*(const CustomVar& other) const
	{
		return 0;
	}
	CustomVar operator/(const CustomVar& other) const
	{
		return 0;
	}
	CustomVar operator%(const CustomVar& other) const
	{
		return 0;
	}

	CustomVar operator++(int) //post
	{
		return 0;
	}
	CustomVar& operator++()
	{
		return 0;
	}

	CustomVar operator--(int) //post
	{
		return 0;
	}
	CustomVar& operator--()
	{
		return 0;
	}

	CustomVar& operator+=(const CustomVar & other)
	{
		return 0;
	}
	CustomVar& operator-=(const CustomVar& other)
	{
		return 0;
	}
	CustomVar& operator*=(const CustomVar& other)
	{
		return 0;
	}
	CustomVar& operator/=(const CustomVar& other)
	{
		return 0;
	}
	CustomVar& operator%=(const CustomVar& other)
	{
		return 0;
	}

	bool operator>(const CustomVar& other) const
	{
		return false;
	}
	bool operator<(const CustomVar& other) const
	{
		return false;
	}
	bool operator==(const CustomVar& other) const
	{
		return false;
	}
	bool operator!=(const CustomVar& other) const
	{
		return false;
	}
	bool operator>=(const CustomVar& other) const
	{
		return false;
	}
	bool operator<=(const CustomVar& other) const
	{
		return false;
	}


	T Get() const { return m_value; }

private:
	template<typename T>
	struct BitReference
	{
		/*This needs whole implementation to be defined :3*/
	private:
		BitReference(/*NEEDS ARGS*/)
		{}
		friend BitReference<T> CustomVar::operator[](size_t offset);
	};
public:
	BitReference<T> operator[](size_t offset) { return BitReference<T>(/*NEEDS ARGS*/); }

private:
	T m_value;
};

#include <string>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const CustomVar<T>& var)
{ return stream << (long long)var.Get(); }