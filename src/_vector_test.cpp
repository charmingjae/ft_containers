/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _vector_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:09:19 by mcha              #+#    #+#             */
/*   Updated: 2022/08/31 00:37:54 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// *==*==*==*==*==*==*==*==*==
// STD
#include <vector>
#include <iostream>

// *==*==*==*==*==*==*==*==*==
// FT
#include "vector.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

template <typename _Tp>
void print(ft::vector<_Tp> &vec)
{
	std::cout << "Size		: " << vec.size() << std::endl;
	std::cout << "Capacity	: " << vec.capacity() << std::endl;
}

template <typename _Tp>
void printVector(ft::vector<_Tp> &vec)
{
	typename ft::vector<_Tp>::iterator it;
	it = vec.begin();
	for (; it != vec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void init_int_vector(ft::vector<int> &vec)
{
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(9);
}

void basic(void)
{
	ft::vector<int> a;
	a.push_back(42);
	a.push_back(1);
	a.push_back(2);
	a.push_back(5);
	a.push_back(1000);
	printVector(a);
	print(a);
}

void iterate(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	std::cout << "Begin : " << *a.begin() << std::endl;
	std::cout << "End : " << *a.end() << std::endl;
	std::cout << "rbegin : " << *a.rbegin() << std::endl;
	std::cout << "rend : " << *a.rend() << std::endl;

	printVector(a);
	print(a);
}

void fnc(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	printVector(a);
	print(a);
	std::cout << "Max_size : " << a.max_size() << std::endl;
	std::cout << "Empty : " << a.empty() << std::endl;
}

void element_access(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	printVector(a);
	print(a);
	std::cout << "operator[0] : " << a[0] << std::endl;
	std::cout << "at : " << a.at(0) << std::endl;
	std::cout << "front : " << a.front() << std::endl;
	std::cout << "back : " << a.back() << std::endl;
}

void resz(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	printVector(a);
	print(a);
	a.resize(1);
	printVector(a);
	print(a);
}

void reserv(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	printVector(a);
	print(a);
	a.reserve(10);
	printVector(a);
	print(a);
}

void clr(void)
{
	ft::vector<int> a;
	init_int_vector(a);
	printVector(a);
	print(a);
	a.clear();
	printVector(a);
	print(a);
}

int main(void)
{
	// 1. Basic test
	// basic();
	// 2. Iterate
	// iterate();
	// 3. Function
	// fnc();
	// 4. Element access
	// element_access();
	// 5. Re
	// resz();
	// reserv();
	// clr();
	// Leak
	system("leaks container");
	return (0);
}