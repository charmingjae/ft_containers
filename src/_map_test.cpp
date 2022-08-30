/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _map_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:38:04 by mcha              #+#    #+#             */
/*   Updated: 2022/08/31 01:06:29 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>

#include "map.hpp"
#include "iterator.hpp"
#include "utility.hpp"

template <typename _Tp1, typename _Tp2>
void print_info(ft::map<_Tp1, _Tp2> &mp)
{
	std::cout << "Size : " << mp.size() << std::endl;
	std::cout << "Empty : " << mp.empty() << std::endl;
}

void basic(void)
{
	ft::map<std::string, int> mp;
	mp.insert(ft::make_pair("b", 1));
	mp.insert(ft::make_pair("c", 1));
	mp.insert(ft::make_pair("d", 1));
	mp.insert(ft::make_pair("e", 1));
	mp.insert(ft::make_pair("f", 1));
	mp.insert(ft::make_pair("a", 1));

	ft::map<std::string, int>::iterator it;

	it = mp.begin();

	for (; it != mp.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;

	print_info(mp);
}

void k_cmp(void)
{
	ft::map<std::string, int> mp;
	mp.insert(ft::make_pair("b", 1));
	mp.insert(ft::make_pair("c", 1));
	mp.insert(ft::make_pair("d", 1));
	mp.insert(ft::make_pair("e", 1));
	mp.insert(ft::make_pair("f", 1));
	mp.insert(ft::make_pair("a", 1));

	ft::map<std::string, int>::key_compare comp = mp.key_comp();
	
	std::string highest = "c";

	ft::map<std::string, int>::iterator it = mp.begin();
	while (comp((*it).first, highest))
	{
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}
}

void v_cmp(void)
{
	ft::map<std::string, int> mp;
	mp.insert(ft::make_pair("b", 1));
	mp.insert(ft::make_pair("c", 1));
	mp.insert(ft::make_pair("d", 1));
	mp.insert(ft::make_pair("e", 1));
	mp.insert(ft::make_pair("f", 1));
	mp.insert(ft::make_pair("a", 1));

	ft::map<std::string, int>::value_compare comp = mp.value_comp();
	
	ft::pair<std::string, int> highest = *++mp.rbegin();

	ft::map<std::string, int>::iterator it = mp.begin();
	while (comp(*it, highest))
	{
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}
}

void eql(void)
{
	ft::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

int main(void)
{
	/// 1. basic
	// basic();
	// k_cmp();
	// v_cmp();
	eql();
	return (0);
}