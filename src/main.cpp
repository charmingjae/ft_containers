/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/08/08 15:44:24 by mcha             ###   ########.fr       */
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

void paper(void)
{
	std::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	std::vector<int>::iterator it = a.begin();
	std::cout << "begin" << std::endl;
	std::cout << *it << std::endl;
	std::cout << *std::next(it, 100) << std::endl;
	std::cout << "end" << std::endl;
}

// --*-- main --*--

int main(void)
{
	paper();
	// test_basic_function();
	// test_constructor_with_parameter();
	return (0);
}

// --*-- Function --*--
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