/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:45:43 by mcha              #+#    #+#             */
/*   Updated: 2022/08/02 22:21:11 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator.hpp>
#include <iterator>
#include <vector.hpp>
// #include <vector>

int main(void)
{
	ft::vector<int> a(7);
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;

	ft::vector<int> b(a);
	return (0);
}