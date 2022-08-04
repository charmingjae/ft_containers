/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:45:43 by mcha              #+#    #+#             */
/*   Updated: 2022/08/04 21:18:21 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator.hpp>
#include <iterator>
#include <vector.hpp>
#include <vector>
#include "temp.hpp"

void test_basic_function(void);
void test_constructor_with_parameter(void);
// template <typename _Tp>
// void print_ft_vector_info(ft::vector<_Tp> &a);
// template <typename _Tp>
// void print_std_vector_info(std::vector<_Tp> &a);

// void paper(void)
// {
// 	std::vector<int>::iterator a;
// }

void test(void)
{
	std::cout << temp::__iterator_traits_impl<int, false>::a << std::endl;
}

int main(void)
{
	test();
	// test_basic_function();
	// test_constructor_with_parameter();
	return (0);
}

// void test_constructor_with_parameter(void)
// {
// 	std::cout << "		test_constructor_with_parameter\n"
// 			  << std::endl;

// 	ft::vector<int> a(9999999, 100);
// 	std::vector<int> b(9999999, 100);
// 	print_ft_vector_info(a);
// 	print_std_vector_info(b);
// }

// void test_basic_function(void)
// {
// 	std::cout << "		test_basic_function\n"
// 			  << std::endl;

// 	std::cout << "--*-- My vector --*--" << std::endl;
// 	ft::vector<int> a(7);
// 	print_ft_vector_info(a);

// 	std::cout << "\n--*-- Original vector --*--" << std::endl;
// 	std::vector<int> b(7);
// 	print_std_vector_info(b);
// }

// template <typename _Tp>
// void print_ft_vector_info(ft::vector<_Tp> &a)
// {
// 	std::cout << "size : " << a.size() << std::endl;
// 	std::cout << "capacity : " << a.capacity() << std::endl;
// 	std::cout << "max_size : " << a.max_size() << std::endl;
// 	std::cout << "empty : " << a.empty() << std::endl;
// 	std::cout << "\n\n"
// 			  << std::endl;
// }

// template <typename _Tp>
// void print_std_vector_info(std::vector<_Tp> &a)
// {
// 	std::cout << "size : " << a.size() << std::endl;
// 	std::cout << "capacity : " << a.capacity() << std::endl;
// 	std::cout << "max_size : " << a.max_size() << std::endl;
// 	std::cout << "empty : " << a.empty() << std::endl;
// 	std::cout << "\n\n"
// 			  << std::endl;
// }