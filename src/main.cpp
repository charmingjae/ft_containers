/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/08/09 14:13:08 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include <iterator>
#include "vector.hpp"
#include <vector>
#include "temp.hpp"

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

// --*-- main --*--

int main(void)
{
	my_push_back();
	// reserve_test();
	// my_resize_test();
	// resize_test();
	// test_basic_function();
	// test_constructor_with_parameter();
	return (0);
}

// --*-- Function --*--

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