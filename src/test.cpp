#include <iostream>

struct TEST
{
	// rename int as test
	typedef int test;
};

template <typename T>
void fnc(typename T::test)
{
	std::cout << "Type in the structure" << std::endl;
	std::cout << sizeof(typename T::test) << std::endl; // diff
}

template <typename T>
void fnc(T)
{
	std::cout << "Only typename T function" << std::endl;
	std::cout << sizeof(typename T::test) << std::endl; // diff
}

int main(void)
{
	fnc<TEST>(10);
	fnc<int>(10);
	return (0);
}