/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tmp.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:15:59 by mcha              #+#    #+#             */
/*   Updated: 2022/08/02 22:46:46 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// --*-- Define --*--
#define _NOEXCEPT throw() // Should I define _NOEXCEPT and _NOEXCEPT_(x)? 2022. 08. 02

// --*-- Include --*--
#include <memory>	 // Allocator
#include <limits>	 // numeric_limits
#include <stdexcept> // standard exception
#include <algorithm> // std::min
#include <iostream>

// --*-- namespace ft --*--
namespace ft
{
	// --*--*--*--*--*--*--*--*--*--*--*-
	// *								*
	// *	 Class : __vector_base		*
	// *								*
	// --*--*--*--*--*--*--*--*--*--*--*-
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

		// --*-- Constructor of vector base --*--
		// * _NOEXCEPT -> No-throw guarantee
		__vector_base() _NOEXCEPT;				  // Basic constructor
		__vector_base(const allocator_type &__a); // Constructor with parameter
		__vector_base(size_type __n);			  // Constructor with size_type
		~__vector_base();						  // Destructor

		// --*-- Member function --*--
		// * Prototype
		void clear(void) _NOEXCEPT; // Clear all of the element in the vector
		size_type max_size(void) const _NOEXCEPT;

		// * Implementation
		size_type capacity(void) const _NOEXCEPT // Get vector whole storage size. Difference with size()
		{
			return static_cast<size_type>(__end_cap_ - __begin_);
		}

		// --*-- Utility for member function --*--
		void __destruct_at_end(pointer __new_last) _NOEXCEPT; // destory vector element from at the end of the vector

	}; // End of __vector_base definition

	// --*-- Constructor & Destructor implementation --*--
	// * 00. Basic constructor
	template <class _Tp, class _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(std::allocator<_Tp>())
	{
	}

	// * 01. Constructor with parameter
	template <class _Tp, class _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a) : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(__a)
	{
		std::cout << "Base with allocator_type" << std::endl;
	}

	// * 02. Constructor with size_type n
	template <class _Tp, class _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(size_type __n) : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(std::allocator<_Tp>())
	{
		if (__n > max_size())										  // 1. Check param __n is bigger than max_size
			this->__throw_length_error("vector : __n is too big");	  // 1-1. if __n is bigger than max_size, throw()
		this->__begin_ = this->__end_ = this->__alloc_.allocate(__n); // 2. Allocate n size
		this->__end_cap_ = this->__begin_ + __n;					  // 3. Set end capacity
	}

	// * 0?. Destructor
	template <class _Tp, class _Allocator>
	__vector_base<_Tp, _Allocator>::~__vector_base()
	{
		if (this->__begin_ != nullptr)
		{
			clear();											   // 1. destroy all element in the vector
			this->__alloc_.deallocate(this->__begin_, capacity()); // 2. deallocate allocated memory
		}
	}

	// --*-- Function implementation --*--
	// * 00. Implementation -> __destruct_at_end()	// * pointer __new_last usually 'begin(__begin_)'
	template <class _Tp, class _Allocator>
	void __vector_base<_Tp, _Allocator>::__destruct_at_end(pointer __new_last) _NOEXCEPT
	{
		pointer __soon_to_be_end = __end_; // Temp pointer variable
		while (__new_last != __soon_to_be_end)
		{
			--__soon_to_be_end;						  // Decrease temp pointer
			this->__alloc_.destroy(__soon_to_be_end); // Destroy element
		}
		__end_ = __new_last; // Change end as parameter
	}

	// * 01. Implementation -> clear()
	template <class _Tp, class _Allocator>
	void __vector_base<_Tp, _Allocator>::clear(void) _NOEXCEPT
	{
		__destruct_at_end(__begin_); // Clear all of the element in the vector using this function
	}

	// * 02. Implementation -> max_size()
	template <typename _Tp, typename _Allocator>
	typename __vector_base<_Tp, _Allocator>::size_type __vector_base<_Tp, _Allocator>::max_size() const _NOEXCEPT
	{
		return static_cast<size_type>(std::min(this->__alloc_.max_size(), static_cast<unsigned long>(std::numeric_limits<difference_type>::max())));
	}

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	// --*--*--*--*--*--*--*--*--*--*--*-
	// *								*
	// *	 	Class : vector			*
	// *								*
	// --*--*--*--*--*--*--*--*--*--*--*-
	template <typename _Tp, typename _Allocator = std::allocator<_Tp> >
	class vector : private __vector_base<_Tp, _Allocator> // Inherit __vector_base as private
	{
	private:
		// --*-- private typedef --*--
		typedef __vector_base<_Tp, _Allocator> __base;
		typedef std::allocator<_Tp> __default_allocator_type;

	public:
		// --*-- public typedef --*--
		typedef vector __self;									  // my self
		typedef _Tp value_type;									  // template parameter value type
		typedef _Allocator allocator_type;						  // template parameter allocator type = Allocator
		typedef typename __base::reference reference;			  // base reference type
		typedef typename __base::const_reference const_reference; // base reference type
		typedef typename __base::size_type size_type;			  // size
		typedef typename __base::difference_type difference_type; // pointer gap
		typedef typename __base::pointer pointer;				  // pointer
		typedef typename __base::const_pointer const_pointer;	  // const pointer

		// --*-- Constructor & Destructor --*--
		vector() _NOEXCEPT;									  // Default constructor with implementation
		explicit vector(const allocator_type &__a) _NOEXCEPT; // Allocator with parameter
		explicit vector(size_type __n);						  // Allocator with size_type n
		vector(size_type __n, const value_type &__x);
		vector(size_type __n, const value_type &__x, const allocator_type &__a);

		// --*-- ! Vector iterator constructor 생각하기 ! --*--
		// --*-- ! Vector iterator constructor 생각하기 ! --*--
		// --*-- ! Vector iterator constructor 생각하기 ! --*--
		~vector();

		// --*-- Member function --*--
		// size ( O )
		// max_size ( O )
		// capacity ( O )
		// empty ( O )
		// resize
		// reserve

		// * Prototype
		size_type max_size() const _NOEXCEPT;

		// * Implementation
		size_type capacity() const _NOEXCEPT { return __base::capacity(); }
		bool empty() const _NOEXCEPT { return this->__begin_ == this->__end_; }
		allocator_type get_allocator() const _NOEXCEPT { return this->__alloc_; }
		size_type size() const _NOEXCEPT { return static_cast<size_type>(this->__end_ - this->__begin_); }

	private:
		// --*-- private member function --*--
		// * Prototype
		void __vallocate(size_type __n);
		void __throw_length_error(const char *__msg) const;
	};

	// --*-- Constructor & Destructor implementation --*--
	// * 00. Basic constructor
	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector() _NOEXCEPT : __vector_base<_Tp, _Allocator>()
	{
	}

	// * 01. Allocator with parameter
	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(const allocator_type &__a) _NOEXCEPT : __base(__a)
	{
	}

	// * 02. Allocator with size_type __n
	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(size_type __n)
	{
		if (__n > 0)
		{
			// __vallocate(__n);												  // 1. allocate
			std::uninitialized_fill(this->__begin_, this->__begin_ + __n, 0); // 2. construct
			this->__end_ += __n;
		}
	}

	// * 0?. Destructor
	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::~vector()
	{ // use __vector_base destructor
	}

	// --*-- Member function implementation --*--
	// * 00. Implementation -> max_size()
	template <typename _Tp, typename _Allocator>
	typename vector<_Tp, _Allocator>::size_type vector<_Tp, _Allocator>::max_size() const _NOEXCEPT
	{
		return __base::max_size();
	}

	// * 01. Implementation -> __vallocate()
	// * Allocate n elements as value 0
	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::__vallocate(size_type __n)
	{
		if (__n > max_size())										  // 1. Check param __n is bigger than max_size
			this->__throw_length_error("vector : __n is too big");	  // 1-1. if __n is bigger than max_size, throw()
		this->__begin_ = this->__end_ = this->__alloc_.allocate(__n); // 2. Allocate n size
		this->__end_cap_ = this->__begin_ + __n;					  // 3. Set end capacity
	}

	// * 02. Implementation -> __throw_length_error()
	// * Handling throw exception
	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::__throw_length_error(const char *__msg) const
	{
		throw std::length_error(__msg);
	}

} // namespace ft

#endif