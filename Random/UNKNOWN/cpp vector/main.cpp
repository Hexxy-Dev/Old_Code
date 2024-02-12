#include <iostream>
#include <vector>

template<typename T>
class Vector
{
public:
	Vector() 
		: m_Size(0)
	{
		m_Data = nullptr;
	}

	~Vector()
	{
		delete[] m_Data;
	}

	void push_back(const T& value)
	{
		m_Size++;
		T* new_Data = new T[m_Size];
		for(size_t i = 0; i < m_Size - 1; i++)
			new_Data[i] = m_Data[i];
		new_Data[m_Size - 1] = value;
		delete[] m_Data;
		m_Data = new_Data;
	}

	void pop_back()
	{
		T* new_Data = new T[m_Size];
		for (size_t i = 0; i < m_Size - 1; i++)
			new_Data[i] = m_Data[i];
		delete[] m_Data;
		m_Data = new_Data;
		m_Size--;
	}

	void reserve(const size_t& value)
	{
		T* new_Data = new T[m_Size + value];
		for (size_t i = 0; i < m_Size; i++)
			new_Data[i] = m_Data[i];
		delete[] m_Data;
		m_Data = new_Data;
		m_Size += value;
	}

	void emplace(const size_t& index, const T& value)
	{
		if (index < m_Size)
			m_Data[index] = value;
		else
			std::cout << "INDEX OUT OF BOUNDS";
	}

	void emplace_back(const T& value)
	{
		m_Data[m_Size - 1] = value;
	}

	size_t size() const
	{
		return m_Size;
	}

	T& operator[](const size_t& index) const
	{
		return m_Data[index];
	}

	T* data() const
	{
		return m_Data;
	}

private:
	T* m_Data;
	size_t m_Size;
};


struct copyTest
{
public:
	int data;
	copyTest(int x = 0)
		: data(x)
	{}

	copyTest(const copyTest& other)
		: data(other.data)
	{
		std::cout << "COPIED!!!!"<<std::endl;
	}
};

int main()
{
	Vector<int> vec1;// = { 5, 2, 3, 2, 5 };
	vec1.push_back(5);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(2);
	vec1.push_back(5);

	vec1.push_back(10);
	for (int i = 0; i < vec1.size(); i++)
	{
		std::cout << vec1[i] << " ";
	}
	std::cout << std::endl;
	vec1.pop_back();
	for (int i = 0; i < vec1.size(); i++)
	{
		std::cout << vec1[i] << " ";
	}

	std::cout << std::endl;
	vec1.reserve(5);
	vec1.emplace(5, 7);
	vec1.emplace(6, 6);
	vec1.emplace(7, 7);
	vec1.emplace(8, 6);
	vec1.emplace_back(7);
	for (int i = 0; i < vec1.size(); i++)
	{
		std::cout << vec1[i] << " ";
	}

	int* vec2 = vec1.data();

	Vector<std::string> vec3;
	vec3.reserve(1);
	vec3[0] = "TEST1";
	vec3.push_back("Test2");
	for (int i = 0; i < vec3.size(); i++)
	{
		std::cout << vec3[i] << " ";
	}

	Vector<copyTest> vec4;
	copyTest test(1);
	vec4.reserve(1);
	vec4.emplace(0, 3);
	vec4.push_back(test);

	for (int i = 0; i < vec4.size(); i++)
	{
		std::cout << vec4[i].data << " ";
	}
}