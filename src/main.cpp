/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/08/11 17:57:11 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include <iterator>
#include "vector.hpp"
#include <vector>
#include <list>
#include <chrono>
#include <stack>
#include "stack.hpp"

// --*-- delete --*--
#define TESTED_TYPE int
#define t_stack_ ft::stack<TESTED_TYPE>
typedef t_stack_::container_type container_type;

template <class T_STACK>
void cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############" << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs < rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs > rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

using namespace std::chrono;
// --*-- function implement --*--

// --*--*--*--*--*--*--*--*--*--*--*--*--*--
// *
// * 	STACK
// *
// --*--*--*--*--*--*--*--*--*--*--*--*--*--

void stack_test(void)
{
	container_type ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_ stck(ctnr);
	t_stack_ stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
					  // return (0);
}

// --*--*--*--*--*--*--*--*--*--*--*--*--*--
// *
// * 	VECTOR
// *
// --*--*--*--*--*--*--*--*--*--*--*--*--*--

// --*-- Basic --*--

template <typename _Tp>
void printSize(ft::vector<_Tp> _vector)
{
	std::cout << _vector.size() << std::endl;
}

template <typename _Tp>
void printSize(std::vector<_Tp> _vector)
{
	std::cout << _vector.size() << std::endl;
}

template <typename _Tp>
void printCapacity(ft::vector<_Tp> _vector)
{
	std::cout << _vector.capacity() << std::endl;
}

template <typename _Tp>
void printCapacity(std::vector<_Tp> _vector)
{
	std::cout << _vector.capacity() << std::endl;
}

template <typename _Tp>
void printVector(ft::vector<_Tp> _vector)
{
	std::cout << "[FT VECTOR] size : " << _vector.size() << " capacity : " << _vector.capacity() << std::endl;
}
template <typename _Tp>
void printVector(std::vector<_Tp> _vector)
{
	std::cout << "[STD VECTOR] size : " << _vector.size() << " capacity : " << _vector.capacity() << std::endl;
}

template <typename _Tp>
void setBasicVector(ft::vector<_Tp> &_vector)
{
	_vector.push_back(1);
	_vector.push_back(2);
	_vector.push_back(3);
	_vector.push_back(4);
	_vector.push_back(5);
	_vector.push_back(6);
}

template <typename _Tp>
void setBasicVector(std::vector<_Tp> &_vector)
{
	_vector.push_back(1);
	_vector.push_back(2);
	_vector.push_back(3);
	_vector.push_back(4);
	_vector.push_back(5);
	_vector.push_back(6);
}

// --*-- Capacity --*--

void std_size_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printSize(a);
}

void ft_size_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printSize(a);
}

void std_max_size_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	std::cout << a.max_size() << std::endl;
}

void ft_max_size_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	std::cout << a.max_size() << std::endl;
}

void std_resize_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	a.resize(100);
	printVector(a);
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.resize(1);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_resize_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	a.resize(100);
	printVector(a);
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.resize(1);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void std_empty_test(void)
{
	std::vector<int> a;
	std::cout << a.empty() << std::endl;
	std::vector<int> b;
	setBasicVector(b);
	std::cout << b.empty() << std::endl;
}

void ft_empty_test(void)
{
	std::vector<int> a;
	std::cout << a.empty() << std::endl;
	std::vector<int> b;
	setBasicVector(b);
	std::cout << b.empty() << std::endl;
}

void std_reserve_test(void)
{
	// 01.
	std::vector<int> a;
	setBasicVector(a);
	a.reserve(100);
	printVector(a);
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// 02.
	a.reserve(1);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_reserve_test(void)
{
	// 01.
	ft::vector<int> a;
	setBasicVector(a);
	a.reserve(100);
	printVector(a);
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// 02.
	a.reserve(1);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// --*-- Element access --*--

void std_operator_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a[0] << " " << a[1] << " " << a[6] << " " << a[-1] << std::endl;
}

void ft_operator_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a[0] << " " << a[1] << " " << a[6] << " " << a[-1] << std::endl;
}

void std_at_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.at(1) << " " << a.at(2) << " " << a.at(5) << " " << std::endl;
}

void ft_at_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.at(1) << " " << a.at(2) << " " << a.at(5) << " " << std::endl;
}

void std_front_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.front() << std::endl;
}

void ft_front_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.front() << std::endl;
}

void std_back_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.back() << std::endl;
}

void ft_back_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::cout << a.back() << std::endl;
}

// --*-- Modifiers --*--

void std_assign_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::vector<int> b;
	b.assign(a.begin(), a.end());
	printVector(b);
	std::vector<int>::iterator it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_assign_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	ft::vector<int> b;
	b.assign(a.begin(), a.end());
	printVector(b);
	ft::vector<int>::iterator it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void std_pop_back_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.pop_back();
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_pop_back_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.pop_back();
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void std_insert_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.insert(a.begin(), 9);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_insert_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.insert(a.begin(), 9);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void std_erase_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.erase(a.begin());
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	printVector(a);
}

void ft_erase_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a.erase(a.begin());
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	printVector(a);
}

void std_swap_test(void)
{
	std::vector<int> a;
	setBasicVector(a);
	printVector(a);

	// iterator
	std::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::vector<int> b;
	printVector(b);

	// iterator
	it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	a.swap(b);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	printVector(b);
	it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_swap_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);
	printVector(a);

	// iterator
	ft::vector<int>::iterator it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	ft::vector<int> b;
	printVector(b);

	// iterator
	it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	a.swap(b);
	printVector(a);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	printVector(b);
	it = b.begin();
	for (; it != b.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void std_clear_test(void)
{
	std::vector<int> a;
	setBasicVector(a);

	printVector(a);
	a.clear();
	printVector(a);
}

void ft_clear_test(void)
{
	ft::vector<int> a;
	setBasicVector(a);

	printVector(a);
	a.clear();
	printVector(a);
}

// --*-- main --*--

void test(void)
{
	stack_test();
	// -- time --
	system_clock::time_point start_time = system_clock::now();
	// --*--*--*--*--*--*--*--*--*--*--*--*--*--
	// *
	// * 	STD RUN CODE
	// *
	// --*--*--*--*--*--*--*--*--*--*--*--*--*--
	// *

	// std_clear_test();
	// std_swap_test();
	// std_erase_test();
	// std_insert_test();
	// std_pop_back_test();
	// std_assign_test();
	// std_back_test();
	// std_front_test();
	// std_at_test();
	// std_operator_test();
	// std_reserve_test();
	// std_empty_test();
	// std_resize_test();
	// std_max_size_test();
	// std_size_test();

	// *
	// --*-- std run code end --*--
	system_clock::time_point end_time = system_clock::now();

	microseconds duration = duration_cast<microseconds>(end_time - start_time);
	// -- time end --
	std::cout << std::endl;
	// -- time --
	system_clock::time_point ft_start_time = system_clock::now();
	// --*--*--*--*--*--*--*--*--*--*--*--*--*--
	// *
	// * 	FT RUN CODE
	// *
	// --*--*--*--*--*--*--*--*--*--*--*--*--*--
	// *

	// ft_clear_test();
	// ft_swap_test();
	// ft_erase_test();
	// ft_insert_test();
	// ft_pop_back_test();
	// ft_assign_test();
	// ft_back_test();
	// ft_front_test();
	// ft_at_test();
	// ft_operator_test();
	// ft_reserve_test();
	// ft_empty_test();
	// ft_resize_test();
	// ft_max_size_test();
	// ft_size_test();

	// *
	// --*-- ft run code end --*--
	std::cout
		<< std::endl;
	system_clock::time_point ft_end_time = system_clock::now();
	microseconds ft_duration = duration_cast<microseconds>(ft_end_time - ft_start_time);
	std::cout << "[STD] " << duration.count() << "ms" << std::endl;
	std::cout << "[FT] " << ft_duration.count() << "ms" << std::endl;
	// -- time end --
}

int main(void)
{
	test();
	// system("leaks container");
	return (0);
}