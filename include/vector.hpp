/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:42:17 by mcha              #+#    #+#             */
/*   Updated: 2022/08/03 00:42:36 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// --*-- Define --*--
#define _NOEXCEPT throw()

// --*-- Include --*--
#include <algorithm> // std::min
#include <limits>	 // numeric_limits
#include <memory>	 // Allocator
#include <stdexcept> // standard exception
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

		// --*-- __vector_base constructor & destructor --*--
		__vector_base() _NOEXCEPT;				  // Basic constructor
		__vector_base(const allocator_type &__a); // With allocator type
		__vector_base(size_type __n);			  // With size
		~__vector_base();						  // Destructor

		// --*-- Member function --*--
		void clear(void) _NOEXCEPT;
		size_type max_size(void) const _NOEXCEPT;

		size_type capacity(void) const _NOEXCEPT
		{
			return static_cast<size_type>(__end_cap_ - __begin_);
		}

		// --*-- Utility function --*--
		void __destruct_at_end(pointer __new_last) _NOEXCEPT; // destory vector element from at the end of the vector
	};

	// --*-- Constructor & Destructor implementation --*--
	// * Basic constructor
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(std::allocator<_Tp>())
	{
	}

	// * With allocator type
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a) : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(__a)
	{
	}

	// * With size
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(size_type __n)
	{
		// 1. allocate
		// 2. set point
	}

} // namespace ft

#endif