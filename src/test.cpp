#include <iostream>
#include <iterator>
#include <vector>

int main(void)
{
	std::vector<int> a(10, 100);
	std::cout << "size : " << a.size() << std::endl;
	std::cout << "capa : " << a.capacity() << std::endl;

	a.clear();
	std::cout << "aft size : " << a.size() << std::endl;
	std::cout << "aft capa : " << a.capacity() << std::endl;
	return (1);
}