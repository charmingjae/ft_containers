#include <iostream>
#include <iterator>
#include <vector>
#include "../include/temp.hpp"

int main(void)
{
	temp::__iterator_traits_impl<float> a;
	std::cout << a.a << std::endl;
	return (1);
}