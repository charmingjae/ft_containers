#include <iostream>
#include <iterator>
#include <vector>

int main(void)
{
	std::vector<int> a(7);
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	return (1);
}