#pragma once

#include "Commons.h"

template<typename T>
struct Vector
{
	
	T* data;
	Vector()
		: size(0), capacity(1)
	{
		data = new T[capacity];
	}

	Vector(const Vector<T>& vec)
	{
		for (size_t i = 0; i < vec.Size(); i++)
			data[i] = vec.data[i];
	}

	void ZeroAllData()
	{
		for (size_t i = 0; i < size; i++)
			data[i] = 0;
	}

	void Clear()
	{
		delete[] data;
		data = new T[capacity];
	}

	void PushBack(const T& x)
	{
		if (size + 1 > capacity)
			Resize(capacity + 1);
		data[size] = x;
		size++;
	}

	void Resize(size_t newCapaciy)
	{
		T* NewData = new T[newCapaciy];
		size_t newSize = (newCapaciy < size) ? newCapaciy : size;
		for (size_t i = 0; i < newSize; i++)
			NewData[i] = data[i];
		delete[] data;
		data = NewData;
		capacity = newCapaciy;
		size = newSize;
	}

	T PopBack()
	{
		size--;
		return data[size];
	}

	T& operator[](size_t index) { return data[index]; }
	T operator[](size_t index) const { return data[index]; }

	size_t Size() { return size; }
	size_t Capacity() { return capacity; }
private:
	size_t size;
	size_t capacity;
};