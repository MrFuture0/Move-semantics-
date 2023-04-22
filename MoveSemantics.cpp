#include <iostream>
#include <string>
#include <algorithm>



class String
{
public:
	String() = default;

	String(const char* text)
	{
		m_index = strlen(text);
		m_text = new char[m_index + 1];
		memcpy(m_text, text, m_index + 1);
	}

	String(const String& other)
	{
		m_index = strlen(other.m_text);
		m_text = new char[m_index+1];
		memcpy(m_text, other.m_text, m_index + 1);
	}

	String(String&& other) noexcept
	{
		std::cout << "moved1" << std::endl;
		m_index = other.m_index;
		m_text = other.m_text;


		other.m_index = 0;
		other.m_text = nullptr;
	}

	String& operator = (String&& other) noexcept
	{
		std::cout << "moved2" << std::endl;
		if (this != &other)
		{
			delete[] m_text;
			m_index = other.m_index;
			m_text = other.m_text;


			other.m_index = 0;
			other.m_text = nullptr;

		}
		return *this;
	}

	void Print()
	{
		std::cout << m_text << std::endl;
	}
	~String()
	{
		std::cout << "deleted" << std::endl;
	}
private:

	uint32_t m_index;
	char* m_text;
};



class Entity
{
public:

	Entity(const String& other)
		:m_name(other)
	{

	}
	Entity(String&& other)
		:m_name(std::move(other))	
	{

	}

	void PrintName()
	{
		m_name.Print();
	}

private:
	String m_name;
};



int main()
{
	String variable1 = "variable1";
	String variable2 = "";

	std::cout << "variable1 :"; variable1.Print();
	std::cout << "variable2 :"; variable2.Print();

	variable2 = std::move(variable1);
	std::cout << "variable2 :"; variable2.Print();
}