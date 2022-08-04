/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:42:17 by mcha              #+#    #+#             */
/*   Updated: 2022/08/04 23:27:42 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// --*-- Define --*--
#define _NOEXCEPT throw()

// --*-- Include --*--
#include <algorithm>	// std::min
#include "iterator.hpp" // iterator
#include <limits>		// numeric_limits
#include <memory>		// allocator
#include <stdexcept>	// standard exception
// --*-- Trash --*--
#include <iostream>

namespace ft
{
	// --*--*--*--*--*--*--*--*--*--*--*-
	//	*
	//	*  		__vector_base
	//	*
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

		// --*-- __vector_base constructor & destructor --*--
		__vector_base() _NOEXCEPT;				  // Basic constructor
		__vector_base(const allocator_type &__a); // With allocator type
		__vector_base(const size_type __n);		  // With size
		__vector_base(const size_type __n,
					  const allocator_type &__a); // With size and allocator type
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
		void __allocate_memory(size_type __n);

		// --*-- Throw function --*--
		void __throw_length_error(const char *__msg) const;
	};

	// --*-- Constructor & Destructor implementation --*--
	// * Basic constructor
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT : __begin_(nullptr),
																__end_(nullptr),
																__end_cap_(nullptr),
																__alloc_(std::allocator<_Tp>())
	{
	}

	// * With allocator type
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a)
		: __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(__a)
	{
	}

	// * With size
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(const size_type __n)
		: __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(std::allocator<_Tp>())
	{
		__allocate_memory(__n);
	}

	// * With size and allocator type
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::__vector_base(const size_type __n, const allocator_type &__a)
		: __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr), __alloc_(__a)
	{
		__allocate_memory(__n);
	}

	// * Destructor
	template <typename _Tp, typename _Allocator>
	__vector_base<_Tp, _Allocator>::~__vector_base()
	{
		if (this->__begin_ != nullptr)
		{
			clear();
			this->__alloc_.deallocate(this->__begin_, capacity());
		}
	}

	// --*-- Member function implementation --*--
	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::clear(void) _NOEXCEPT
	{
		__destruct_at_end(this->__begin_);
	}

	template <typename _Tp, typename _Allocator>
	typename __vector_base<_Tp, _Allocator>::size_type __vector_base<_Tp, _Allocator>::max_size() const _NOEXCEPT
	{
		return static_cast<size_type>(
			std::min(this->__alloc_.max_size(), static_cast<unsigned long>(std::numeric_limits<difference_type>::max())));
	}

	// --*-- Utility function implementation --*--
	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__destruct_at_end(pointer __new_last) _NOEXCEPT
	{
		pointer __soon_to_be_end = __end_;
		while (__new_last != __soon_to_be_end)
		{
			--__soon_to_be_end;
			this->__alloc_.destroy(__soon_to_be_end);
		}
		__end_ = __new_last;
	}

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__allocate_memory(size_type __n)
	{
		if (__n > max_size())
			this->__throw_length_error("vector : size __n is too big");
		this->__begin_ = this->__end_ = this->__alloc_.allocate(__n); // 1. allocate and set begin, end
		this->__end_cap_ = this->__begin_ + __n;					  // 2. set point
	}

	// --*-- Throw function implementation --*--
	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__throw_length_error(const char *__msg) const
	{
		throw std::length_error(__msg);
	}

	// --*--*--*--*--*--*--*--*--*--*--*-
	//	*
	//	*  			vector
	//	*
	// --*--*--*--*--*--*--*--*--*--*--*-
	template <typename _Tp, typename _Allocator = std::allocator<_Tp> >
	class vector : private __vector_base<_Tp, _Allocator> // Inherit __vector_base
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

		// --*-- vector class constructor & destructor --*--
		vector() _NOEXCEPT;
		explicit vector(const allocator_type &__a) _NOEXCEPT;
		explicit vector(const size_type __n);
		vector(const size_type __n, const value_type &__x);
		vector(const size_type __n, const value_type &__x, const allocator_type &__a);
		~vector();

		// --*-- Member function --*--
		size_type max_size(void) const _NOEXCEPT;
		// * Implementation
		size_type capacity(void) const _NOEXCEPT
		{
			return __base::capacity();
		}
		bool empty(void) const _NOEXCEPT
		{
			return this->__begin_ == this->__end_;
		}
		allocator_type get_allocator(void) const _NOEXCEPT
		{
			return this->__alloc_;
		}
		size_type size(void) const _NOEXCEPT
		{
			return static_cast<size_type>(this->__end_ - this->__begin_);
		}
	};

	// --*-- vector constructor & destructor implementation --*--
	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector() _NOEXCEPT : __base()
	{
	}

	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(const allocator_type &__a) _NOEXCEPT : __base(__a)
	{
	}

	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(const size_type __n) : __base(__n)
	{
		if (__n > 0)
		{
			// Memory is already allocated at __base(__n)
			std::uninitialized_fill(this->__begin_, this->__begin_ + __n, value_type());
			this->__end_ += __n;
		}
	}

	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(const size_type __n, const value_type &__x) : __base(__n)
	{
		if (__n > 0)
		{
			// Memory is already allocated at __base(__n)
			std::uninitialized_fill(this->__begin_, this->__begin_ + __n, __x);
			this->__end_ += __n;
		}
	}

	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::vector(const size_type __n, const value_type &__x, const allocator_type &__a)
		: __base(__n, __a)
	{
		if (__n > 0)
		{
			// Memory is already allocated at __base(__n)
			std::uninitialized_fill(this->__begin_, this->__begin_ + __n, __x);
			this->__end_ += __n;
		}
	}

	template <typename _Tp, typename _Allocator>
	vector<_Tp, _Allocator>::~vector()
	{
	}

	// --*-- Member function implementation --*--
	template <typename _Tp, typename _Allocator>
	typename vector<_Tp, _Allocator>::size_type vector<_Tp, _Allocator>::max_size(void) const _NOEXCEPT
	{
		return __base::max_size();
	}

	// --*--*--*--*--*--*--*--*--*--*--*-
	//	*
	//	*  		vector iterator
	//	*
	// --*--*--*--*--*--*--*--*--*--*--*-

	template <typename _Iter>
	class __vector_iter
	{
	public:
		typedef _Iter iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;

	private:
		iterator_type __i;

	public:
		__vector_iter() _NOEXCEPT;
		template <typename _Up>
		__vector_iter(const __vector_iter<_Up> &__u,
					  typename enable_if<is_same<_Up, random_access_iterator_tag>::value>::type * = 0) _NOEXCEPT
			: __i(__u.base())
		{
		}

		// --*-- Function --*--
		iterator_type base() const _NOEXCEPT;

		// --*-- Operation --*--
		reference operator*() const _NOEXCEPT;
		pointer operator->() const _NOEXCEPT;
		__vector_iter &operator++() _NOEXCEPT;
		__vector_iter operator++(int) _NOEXCEPT;
		__vector_iter &operator--() _NOEXCEPT;
		__vector_iter operator--(int) _NOEXCEPT;
		__vector_iter operator+(difference_type __n) const _NOEXCEPT;
		__vector_iter &operator+=(difference_type __n) _NOEXCEPT;
		__vector_iter operator-(difference_type __n) const _NOEXCEPT;
		__vector_iter &operator-=(difference_type __n) _NOEXCEPT;
		reference operator[](difference_type __n) const _NOEXCEPT;

	private:
		__vector_iter(iterator_type __x) _NOEXCEPT : __i(__x)
		{
		}
	};

	template <typename _Iter>
	__vector_iter<_Iter>::__vector_iter() _NOEXCEPT
	{
	}

	template <typename _Iter>
	typename __vector_iter<_Iter>::iterator_type __vector_iter<_Iter>::base() const _NOEXCEPT
	{
		return __i;
	}

	// --*-- Operation implementation --*--
	template <typename _Iter>
	typename __vector_iter<_Iter>::reference __vector_iter<_Iter>::operator*() const _NOEXCEPT
	{
		return *__i;
	}

	template <typename _Iter>
	typename __vector_iter<_Iter>::pointer __vector_iter<_Iter>::operator->() const _NOEXCEPT
	{
		// return (pointer)(&(*__i));
		return __i;
	}

	template <typename _Iter>
	__vector_iter<_Iter> &__vector_iter<_Iter>::operator++() _NOEXCEPT
	{
		++__i;
		return *this;
	}

	template <typename _Iter>
	__vector_iter<_Iter> __vector_iter<_Iter>::operator++(int) _NOEXCEPT
	{
		__vector_iter __tmp(*this);
		++(*this);
		return __tmp;
	}

	template <typename _Iter>
	__vector_iter<_Iter> &__vector_iter<_Iter>::operator--() _NOEXCEPT
	{
		--__i;
		return *this;
	}

	template <typename _Iter>
	__vector_iter<_Iter> __vector_iter<_Iter>::operator--(int) _NOEXCEPT
	{
		__vector_iter __tmp(*this);
		--(*this);
		return __tmp;
	}

	template <typename _Iter>
	__vector_iter<_Iter> __vector_iter<_Iter>::operator+(difference_type __n) const _NOEXCEPT
	{
		__vector_iter __w(*this);
		__w += __n;
		return __w;
	}

	template <typename _Iter>
	__vector_iter<_Iter> &__vector_iter<_Iter>::operator+=(difference_type __n) _NOEXCEPT
	{
		__i += __n;
		return *this;
	}

	template <typename _Iter>
	__vector_iter<_Iter> __vector_iter<_Iter>::operator-(difference_type __n) const _NOEXCEPT
	{
		return *this + (-__n);
	}

	template <typename _Iter>
	__vector_iter<_Iter> &__vector_iter<_Iter>::operator-=(difference_type __n) _NOEXCEPT
	{
		*this += -__n;
		return *this;
	}

	template <typename _Iter>
	typename __vector_iter<_Iter>::reference __vector_iter<_Iter>::operator[](difference_type __n) const _NOEXCEPT
	{
		return __i[__n];
	}

	// --*-- NON - MEMBER FUNCTION (friend operation) --*--

	template <class _Iter1, class _Iter2>
	bool operator==(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() == __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator<(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() < __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator!=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__x == __y);
	}

	template <class _Iter1, class _Iter2>
	bool operator>(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __y < __x;
	}

	template <class _Iter1, class _Iter2>
	bool operator>=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__x < __y);
	}

	template <class _Iter1, class _Iter2>
	bool operator<=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__y < __x);
	}

	template <class _Iter1>
	bool operator!=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__x == __y);
	}

	template <class _Iter1>
	bool operator>(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return __y < __x;
	}

	template <class _Iter1>
	bool operator>=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__x < __y);
	}

	template <class _Iter1>
	bool operator<=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__y < __x);
	}

	template <class _Iter1, class _Iter2>
	typename __vector_iter<_Iter1>::difference_type operator-(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() - __y.base();
	}

	template <class _Iter>
	__vector_iter<_Iter> operator+(typename __vector_iter<_Iter>::difference_type __n, __vector_iter<_Iter> __x) _NOEXCEPT
	{
		__x += __n;
		return __x;
	}

} // namespace ft

#endif