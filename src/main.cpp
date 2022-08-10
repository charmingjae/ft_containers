/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/08/10 19:17:48 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include <iterator>
#include "vector.hpp"
#include <vector>

void test_basic_function(void);
void test_constructor_with_parameter(void);
template <typename _Tp>
void print_ft_vector_info(ft::vector<_Tp> &a);
template <typename _Tp>
void print_std_vector_info(std::vector<_Tp> &a);
void resize_test(void);
void my_resize_test(void);
void reserve_test(void);
void my_push_back(void);
void my_iterator_constructor(void);
void my_assign_test(void);
void my_insert_test_1(void);
void my_insert_test_2(void);
void my_insert_test_3(void);
void erase_test_1(void);
void erase_test_2(void);
void resize_tester(void);
void insert_tester(void);
void assign_tester(void);
void operator_tester(void);

// --*-- main --*--

int main(void)
{
	operator_tester();
	// assign_tester();
	// insert_tester();
	// resize_tester();
	// erase_test_2();
	// erase_test_1();
	// my_insert_test_3();
	// my_insert_test_2();
	// my_insert_test_1();
	// my_assign_test();
	// my_iterator_constructor();
	// my_push_back();
	// reserve_test();
	// my_resize_test();
	// resize_test();
	// test_basic_function();
	// test_constructor_with_parameter();
	// system("leaks container");
	return (0);
}

// --*-- Function --*--

void operator_tester(void)
{
	ft::vector<float> ft_a;
	ft_a.push_back(10);
	ft_a.push_back(20);
	ft_a.push_back(30);
	ft::vector<float> ft_b;
	ft_b.push_back(10.42f);
	ft_b.push_back(20);
	ft_b.push_back(30.33f);
	std::cout << (ft_a != ft_b) << std::endl;
}

void assign_tester(void)
{
	ft::vector<int> a;
	a.assign(100, 1);

	std::vector<int> b;
	b.assign(100, 1);

	std::cout << "ft size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	std::cout << "std size : " << b.size() << " capacity : " << b.capacity() << std::endl;
}

void insert_tester(void)
{
	ft::vector<std::string> ft_c0(4, "___");
	std::vector<std::string> std_c0(4, "___");

	ft_c0.insert(ft_c0.begin(), 1, "A");
	std_c0.insert(std_c0.begin(), 1, "A");
	for (ft::vector<std::string>::iterator it = ft_c0.begin(); it != ft_c0.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	for (std::vector<std::string>::iterator it = std_c0.begin(); it != std_c0.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	ft_c0.insert(ft_c0.begin(), 1, "B");
	std_c0.insert(std_c0.begin(), 1, "B");
	for (ft::vector<std::string>::iterator it = ft_c0.begin(); it != ft_c0.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	for (std::vector<std::string>::iterator it = std_c0.begin(); it != std_c0.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void resize_tester(void)
{
	ft::vector<int> ft(3);
	std::vector<int> std(3);
	std::cout << "ft size : " << ft.size() << std::endl;
	std::cout << "std size : " << std.size() << std::endl;

	ft.resize(5);
	std.resize(5);
	std::cout << "ft size : " << ft.size() << std::endl;
	std::cout << "std size : " << std.size() << std::endl;
}

void erase_test_1(void)
{
	ft::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	std::cout << "init size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// erase
	std::cout << "erase return : " << *a.erase(a.begin()) << std::endl;
	std::cout << "after size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void erase_test_2(void)
{
	std::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	std::cout << "init size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// erase
	std::cout << "erase return : " << *a.erase(a.begin() + 1, a.begin() + 3) << std::endl;
	std::cout << "after size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void my_insert_test_3(void)
{
	ft::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	std::cout << "init size : " << a.size() << " capacity : " << a.capacity() << std::endl;

	ft::vector<int> b;
	b.push_back(100);
	b.push_back(100);
	b.push_back(100);

	a.insert(a.begin() + 1, b.begin(), b.end());
	std::cout << "after size : " << a.size() << " capacity : " << a.capacity() << std::endl;

	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void my_insert_test_2(void)
{
	ft::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	std::cout << "init size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	a.insert(a.begin() + 1, 100, 9);
	std::cout << "init size : " << a.size() << " capacity : " << a.capacity() << std::endl;
}

void my_insert_test_1(void)
{
	std::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	// a.push_back(5);
	std::cout << "size : " << a.size() << " cap : " << a.capacity() << std::endl;
	std::cout << "insert result : " << *a.insert(a.begin(), 9) << std::endl;
	std::cout << "after size : " << a.size() << " capacity : " << a.capacity() << std::endl;
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void my_assign_test(void)
{
	std::vector<int> a;
	a.assign(10, 7);
	std::cout << "size : " << a.size() << " cap : " << a.capacity() << std::endl;
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// my assign
	ft::vector<int> b;
	b.assign(10, 7);
	std::cout << "my size : " << b.size() << " my cap : " << b.capacity() << std::endl;
	ft::vector<int>::iterator it2 = b.begin();
	for (; it2 != b.end(); it2++)
	{
		std::cout << *it2 << " ";
	}
	std::cout << std::endl;
}

void my_iterator_constructor(void)
{
	// std::vector<int> test;
	// test.push_back(1);
	// test.push_back(2);
	// test.push_back(3);
	// test.push_back(4);
	// test.push_back(5);
	// std::vector<int> b(test.begin(), test.end());
	// std::cout << "size : " << b.size() << std::endl;
	// std::cout << "capacity : " << b.capacity() << std::endl;
	// std::vector<int>::iterator it = b.begin();
	// for (; it != b.end(); it++)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;

	// ft::vector<int> origin;
	// origin.push_back(1);
	// origin.push_back(2);
	// origin.push_back(3);
	// origin.push_back(4);
	// origin.push_back(5);

	// ft::vector<int> c(origin.begin(), origin.end());
	// std::cout << "size : " << c.size() << std::endl;
	// std::cout << "capacity : " << c.capacity() << std::endl;
	// ft::vector<int>::iterator it2 = c.begin();
	// for (; it2 != c.end(); it2++)
	// {
	// 	std::cout << *it2 << " ";
	// }
	// std::cout << std::endl;
}

void my_push_back(void)
{
	ft::vector<int> origin;
	origin.push_back(10);
	origin.push_back(10);
	origin.push_back(10);
	origin.push_back(10);
	origin.push_back(10);
	std::cout << "origin size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;

	std::vector<int> system;
	system.push_back(10);
	system.push_back(10);
	system.push_back(10);
	system.push_back(10);
	system.push_back(10);
	std::cout << "system size : " << system.size() << std::endl;
	std::cout << "system init cap : " << system.capacity() << std::endl;
}

void my_resize_test(void)
{
	ft::vector<int> my;
	std::cout << "my size : " << my.size() << std::endl;
	std::cout << "my init cap : " << my.capacity() << std::endl;

	my.resize(10);
	std::cout << "after size : " << my.size() << std::endl;
	std::cout << "after init cap : " << my.capacity() << std::endl;
}

void my_reserve_test(void)
{
	std::vector<int> origin;
	origin.push_back(1);
	origin.push_back(2);
	origin.push_back(3);
	origin.push_back(4);
	origin.push_back(5);
	std::cout << "origin init size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;
	origin.reserve(20);
	std::cout << std::endl;
	std::cout << "origin init size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;
	std::cout << std::endl;

	std::vector<int>::iterator it = origin.begin();
	for (; it != origin.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void reserve_test(void)
{
	std::vector<int> origin;
	origin.push_back(1);
	origin.push_back(2);
	origin.push_back(3);
	origin.push_back(4);
	origin.push_back(5);
	std::cout << "origin init size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;
	origin.reserve(20);
	std::cout << std::endl;
	std::cout << "origin init size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;
	std::cout << std::endl;

	std::vector<int>::iterator it = origin.begin();
	for (; it != origin.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void resize_test(void)
{
	std::vector<int> origin;
	origin.push_back(1);
	origin.push_back(2);
	origin.push_back(3);
	origin.push_back(4);
	origin.push_back(5);
	std::cout << "origin init size : " << origin.size() << std::endl;
	std::cout << "origin init cap : " << origin.capacity() << std::endl;
	std::vector<int>::iterator originIt = origin.begin();
	for (; originIt != origin.end(); originIt++)
	{
		std::cout << *originIt << " ";
	}
	std::cout << "\n"
			  << std::endl;
	origin.resize(10);

	std::cout << "origin resize size : " << origin.size() << std::endl;
	std::cout << "origin resize cap : " << origin.capacity() << std::endl;
	originIt = origin.begin();
	for (; originIt != origin.end(); originIt++)
	{
		std::cout << *originIt << " ";
	}
	std::cout << "\n"
			  << std::endl;
}

void test_constructor_with_parameter(void)
{
	std::cout << "		test_constructor_with_parameter\n"
			  << std::endl;

	ft::vector<int> a(9999999, 100);
	std::vector<int> b(9999999, 100);
	print_ft_vector_info(a);
	print_std_vector_info(b);
}

void test_basic_function(void)
{
	std::cout << "		test_basic_function\n"
			  << std::endl;

	std::cout << "--*-- My vector --*--" << std::endl;
	ft::vector<int> a(7);
	print_ft_vector_info(a);

	std::cout << "\n--*-- Original vector --*--" << std::endl;
	std::vector<int> b(7);
	print_std_vector_info(b);
}

template <typename _Tp>
void print_ft_vector_info(ft::vector<_Tp> &a)
{
	std::cout << "size : " << a.size() << std::endl;
	std::cout << "capacity : " << a.capacity() << std::endl;
	std::cout << "max_size : " << a.max_size() << std::endl;
	std::cout << "empty : " << a.empty() << std::endl;
	std::cout << "\n\n"
			  << std::endl;
}

template <typename _Tp>
void print_std_vector_info(std::vector<_Tp> &a)
{
	std::cout << "size : " << a.size() << std::endl;
	std::cout << "capacity : " << a.capacity() << std::endl;
	std::cout << "max_size : " << a.max_size() << std::endl;
	std::cout << "empty : " << a.empty() << std::endl;
	std::cout << "\n\n"
			  << std::endl;
}