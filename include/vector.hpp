/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:42:17 by mcha              #+#    #+#             */
/*   Updated: 2022/08/02 22:47:37 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// --*-- Define --*--
#define _NOEXCEPT throw()

// --*-- Include --*--
#include <memory>	 // Allocator
#include <limits>	 // numeric_limits
#include <stdexcept> // standard exception
#include <algorithm> // std::min
// --*-- Trash --*--
#include <iostream>

namespace ft
{
	//	--*--
	//	*
	//	*  __vector_base
	//	*
	//	--*--
	template <typename _Tp, typename _Allocator = std::allocator<_Tp> >
	class __vector_base
	{
	public:
		// --*-- public typedef --*--
		typedef _Allocator allocator_type;					  // typedef allocator_type
		typedef typename allocator_type::size_type size_type; // typedef size_type

	protected:
		// --*-- protected typedef --*--
		typedef _Tp value_type;											  // template parameter value type
		typedef value_type &reference;									  // reference value type
		typedef const value_type &const_reference;						  // const reference value type
		typedef typename allocator_type::pointer pointer;				  // pointer
		typedef typename allocator_type::const_pointer const_pointer;	  // const pointer
		typedef typename allocator_type::difference_type difference_type; // gap of pointer
		typedef pointer iterator;										  // iterator
		typedef const_pointer const_iterator;							  // const iterator

		// --*-- Pointer variable --*--
		pointer __begin_;		 // Pointer that point first element in the vector
		pointer __end_;			 // Pointer that point last element in the vector
		pointer __end_cap_;		 // Pointer that point last allocated area in the vector
		allocator_type __alloc_; // Allocator keep in current vector
	};
}

#endif