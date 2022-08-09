/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:42:17 by mcha              #+#    #+#             */
/*   Updated: 2022/08/09 23:24:18 by mcha             ###   ########.fr       */
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
		void __clear(void) _NOEXCEPT;
		size_type max_size(void) const _NOEXCEPT;

		size_type capacity(void) const _NOEXCEPT
		{
			return static_cast<size_type>(__end_cap_ - __begin_);
		}
		size_type __size(void) const _NOEXCEPT
		{
			return static_cast<size_type>(this->__end_ - this->__begin_);
		}
		// --*-- Modifiers --*--
		void __swap(__vector_base &x)
		{
			// tmp
			pointer tmp_beg = this->__begin_;
			pointer tmp_end = this->__end_;
			pointer tmp_cap = this->__end_cap_;
			allocator_type tmp_all = this->__alloc_;
			// this
			this->__begin_ = x.__begin_;
			this->__end_ = x.__end_;
			this->__end_cap_ = x.__end_cap_;
			this->__alloc_ = x.__alloc_;
			// x
			x.__begin_ = tmp_beg;
			x.__end_ = tmp_end;
			x.__end_cap_ = tmp_cap;
			x.__alloc_ = tmp_all;
		}

		// --*-- Utility function --*--
		void __destruct_at_end(pointer __new_last) _NOEXCEPT; // destory vector element from at the end of the vector
		void __allocate_memory(size_type __n);
		void __construct_at_end(size_type __n);
		void __construct_at_end(size_type __n, const_reference __x);
		template <typename _ForwardIterator>
		void __construct_at_end(_ForwardIterator __first, _ForwardIterator __last);
		void __append(size_type __n);
		void __append(size_type __n, const_reference __x);

		// --*-- Throw function --*--
		void __throw_length_error(const char *__msg) const;
		void __throw_out_of_range(const char *__msg) const;

	}; // End __vector_base class

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
			__clear();
			this->__alloc_.deallocate(this->__begin_, capacity());
		}
	}

	// --*-- Member function implementation --*--
	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__clear(void) _NOEXCEPT
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

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__construct_at_end(size_type __n)
	{
		// _ConstructTransaction __tx(*this, __n);
		// for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_)
		// {
		// 	__alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_));
		// }
		pointer __now_end_ = this->__end_;
		pointer __new_end_ = this->__end_ + __n;

		for (; __now_end_ != __new_end_; ++__now_end_)
		{
			this->__alloc_.construct(__now_end_);
		}
	}

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
	{
		// _ConstructTransaction __tx(*this, __n);
		// for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_)
		// {
		// 	__alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_), __x);
		// }
		// _ConstructTransaction
		pointer __now_end_ = this->__end_;		 // now position
		pointer __new_end_ = this->__end_ + __n; // new position

		for (; __now_end_ != __new_end_; ++__now_end_)
		{
			this->__alloc_.construct(__now_end_, __x);
		}
	}
	template <typename _Tp, typename _Allocator>
	template <typename _ForwardIterator>
	void __vector_base<_Tp, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last)
	{
		std::uninitialized_copy(__first, __last, this->__begin_); // check Exception Safety
		this->__end_ += this->__size();
	}

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__append(size_type __n)
	{
		if (static_cast<size_type>(this->__end_cap_ - this->__end_) >= __n) // has enough storage
		{
			this->__construct_at_end(__n);
		}
		else // not enough storage
		{
			// 1. reallocate
			__vector_base<_Tp, _Allocator> __tmp_(__n);
			// 2. 기존 것 넣기
			std::uninitialized_copy(this->__begin_, this->__end_, __tmp_.__begin_); // check Exception Safety
			__tmp_.__end_ += this->__size();
			// 3. 스왑
			this->__swap(__tmp_);
		}
	}

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
	{
		if (static_cast<size_type>(this->__end_cap_ - this->__end_) >= __n) // has enough storage
		{
			this->__construct_at_end(__n, __x);
		}
		else // not enough storage
		{
			// ------------------------------------------------------------> 구현
			// 1. reallocate
			__vector_base<_Tp, _Allocator> __tmp_(__n);
			// 2. 기존 것 넣기
			std::uninitialized_copy(this->__begin_, this->__end_, __tmp_.__begin_); // check Exception Safety
			__tmp_.__end_ += this->__size();
			// 3. 스왑
			this->__swap(__tmp_);
		}
	}

	// --*-- Throw function implementation --*--
	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__throw_length_error(const char *__msg) const
	{
		throw std::length_error(__msg);
	}

	template <typename _Tp, typename _Allocator>
	void __vector_base<_Tp, _Allocator>::__throw_out_of_range(const char *__msg) const
	{
		throw std::out_of_range(__msg);
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
		// --*-- Constructor
		__vector_iter() _NOEXCEPT {}
		template <typename _Up>
		__vector_iter(const __vector_iter<_Up> &__u,
					  typename enable_if<__is_random_access_iterator<_Up>::value>::type * = 0) _NOEXCEPT
			: __i(__u.base())
		{
		}
		__vector_iter(iterator_type __x) _NOEXCEPT : __i(__x)
		{
		}

		// --*-- Member function (operator)
		reference operator*() const _NOEXCEPT
		{
			return *__i;
		}

		pointer operator->() const _NOEXCEPT
		{
			return (pointer)(__i);
		}

		__vector_iter &operator++() _NOEXCEPT
		{
			++__i;
			return *this;
		}

		__vector_iter operator++(int) _NOEXCEPT
		{
			__vector_iter __tmp(*this);
			++(*this);
			return __tmp;
		}

		__vector_iter &operator--() _NOEXCEPT
		{
			--__i;
			return *this;
		}

		__vector_iter operator--(int) _NOEXCEPT
		{
			__vector_iter __tmp(*this);
			--(*this);
			return __tmp;
		}

		__vector_iter operator+(difference_type __n) const _NOEXCEPT
		{
			__vector_iter __w(*this);
			__w += __n;
			return __w;
		}

		__vector_iter &operator+=(difference_type __n) _NOEXCEPT
		{
			__i += __n;
			return *this;
		}

		__vector_iter operator-(difference_type __n) const _NOEXCEPT
		{
			return *this + (-__n);
		}

		__vector_iter &operator-=(difference_type __n) _NOEXCEPT
		{
			*this += -__n;
			return *this;
		}

		reference operator[](difference_type __n) const _NOEXCEPT
		{
			return __i[__n];
		}

		iterator_type base() const _NOEXCEPT { return __i; }
	};

	// --*-- Non-member function (operator) implementation --*--
	template <typename _Iter1, typename _Iter2>
	bool operator==(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() == __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator<(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() < __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator!=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__x == __y);
	}

	template <typename _Iter1, typename _Iter2>
	bool operator>(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __y < __x;
	}

	template <typename _Iter1, typename _Iter2>
	bool operator>=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__x < __y);
	}

	template <typename _Iter1, typename _Iter2>
	bool operator<=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return !(__y < __x);
	}

	template <typename _Iter1>
	bool operator!=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__x == __y);
	}

	template <typename _Iter1>
	bool operator>(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return __y < __x;
	}

	template <typename _Iter1>
	bool operator>=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__x < __y);
	}

	template <typename _Iter1>
	bool operator<=(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter1> &__y) _NOEXCEPT
	{
		return !(__y < __x);
	}

	template <typename _Iter1, typename _Iter2>
	typename __vector_iter<_Iter1>::difference_type
	operator-(const __vector_iter<_Iter1> &__x, const __vector_iter<_Iter2> &__y) _NOEXCEPT
	{
		return __x.base() - __y.base();
	}

	template <typename _Iter>
	__vector_iter<_Iter>
	operator+(typename __vector_iter<_Iter>::difference_type __n, __vector_iter<_Iter> __x) _NOEXCEPT
	{
		__x += __n;
		return __x;
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

		typedef __vector_iter<pointer> iterator;							 // iterator
		typedef __vector_iter<const_pointer> const_iterator;				 // const iterator
		typedef ft::reverse_iterator<iterator> reverse_iterator;			 // reverse iterator
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; // const reverse interator

		// --*-- vector class constructor & destructor --*--
		vector() _NOEXCEPT;
		explicit vector(const allocator_type &__a) _NOEXCEPT;
		explicit vector(const size_type __n);
		vector(const size_type __n, const value_type &__x);
		vector(const size_type __n, const value_type &__x, const allocator_type &__a);
		vector(const vector &x);
		template <typename _InputIterator>
		vector(_InputIterator __first,
			   typename enable_if<__is_input_iterator<_InputIterator>::value &&
									  !__is_forward_iterator<_InputIterator>::value,
								  _InputIterator>::type __last,
			   const allocator_type &alloc = allocator_type());
		template <typename _ForwardIterator>
		vector(_ForwardIterator __first,
			   typename enable_if<__is_forward_iterator<_ForwardIterator>::value,
								  _ForwardIterator>::type __last,
			   const allocator_type &alloc = allocator_type());
		~vector();

		// --*-- Member function --*--

		// --*-- Capacity member function
		size_type size(void) const _NOEXCEPT
		{
			return this->__size();
			// return static_cast<size_type>(this->__end_ - this->__begin_);
		}
		size_type max_size(void) const _NOEXCEPT;
		void resize(size_type __sz);
		void resize(size_type __sz, const_reference __x);
		size_type capacity(void) const _NOEXCEPT
		{
			return __base::capacity();
		}
		bool empty(void) const _NOEXCEPT
		{
			return this->__begin_ == this->__end_;
		}

		void reserve(size_type __n)
		{
			if (__n > capacity())
			{
				vector<_Tp, _Allocator> __tmp_(__n, value_type(), this->__alloc_);
				std::uninitialized_copy(this->__begin_, this->__end_, __tmp_.__begin_); // check Exception Safety
				__tmp_.__end_ = __tmp_.__begin_ + this->size();
				swap(__tmp_);
			}
		}

		// --*-- Element access member function
		reference operator[](size_type __n) _NOEXCEPT
		{
			return this->__begin_[__n];
		}
		const_reference operator[](size_type __n) const _NOEXCEPT
		{
			return this->__begin_[__n];
		}
		reference at(size_type __n)
		{
			if (__n >= size())
				this->__throw_out_of_range("vector : out of range");
			return this->__begin_[__n];
		}
		const_reference at(size_type __n) const
		{
			if (__n >= size())
				this->__throw_out_of_range("vector : out of range");
			return this->__begin_[__n];
		}
		reference front()
		{
			return *this->__begin_;
		}
		const_reference front() const
		{
			return *this->__begin_;
		}
		reference back()
		{
			return *(this->__end_ - 1);
		}
		const_reference back() const
		{
			return *(this->__end_ - 1);
		}

		// --*-- Iterator member function
		iterator begin() _NOEXCEPT
		{
			return this->__begin_;
		}
		const_iterator begin() const _NOEXCEPT
		{
			return this->__begin_;
		}
		iterator end() _NOEXCEPT
		{
			return this->__end_;
		}
		const_iterator end() const _NOEXCEPT
		{
			return this->__end_;
		}
		reverse_iterator rbegin() _NOEXCEPT
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const _NOEXCEPT
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() _NOEXCEPT
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const _NOEXCEPT
		{
			return const_reverse_iterator(begin());
		}

		// --*-- Allocator --*--
		allocator_type get_allocator(void) const _NOEXCEPT
		{
			return this->__alloc_;
		}

		// --*-- Modifiers --*--
		template <typename _InputIterator>
		typename enable_if<__is_input_iterator<_InputIterator>::value &&
							   !__is_forward_iterator<_InputIterator>::value,
						   void>::type
		assign(_InputIterator __first, _InputIterator __last);

		template <typename _ForwardIterator>
		typename enable_if<
			__is_forward_iterator<_ForwardIterator>::value,
			void>::type
		assign(_ForwardIterator __first, _ForwardIterator __last);

		void assign(size_type __n, const_reference __u);

		void push_back(const_reference __x);

		void pop_back();

		// insert
		iterator insert(iterator position, const value_type &val);
		void insert(iterator position, size_type n, const value_type &val);
		template <typename InputIterator>
		void insert(iterator position, InputIterator first,
					typename enable_if<__is_input_iterator<InputIterator>::value &&
										   !__is_forward_iterator<InputIterator>::value,
									   InputIterator>::type last);
		template <typename ForwardIterator>
		void insert(iterator position, ForwardIterator first,
					typename enable_if<__is_forward_iterator<ForwardIterator>::value,
									   ForwardIterator>::type last);

		void swap(vector &x);

		void clear();
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
	vector<_Tp, _Allocator>::vector(const size_type __n) : __base(__n, allocator_type())
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
			// std::uninitialized_fill(this->__begin_, this->__begin_ + __n, __x);
			std::uninitialized_fill_n(this->__begin_, __n, __x);
			this->__end_ += __n;
		}
	}

	template <typename _Tp, typename _Allocator>
	template <typename _InputIterator>
	vector<_Tp, _Allocator>::vector(_InputIterator __first,
									typename enable_if<__is_input_iterator<_InputIterator>::value &&
														   !__is_forward_iterator<_InputIterator>::value,
													   _InputIterator>::type __last,
									const allocator_type &alloc) : __base(alloc)
	{
		for (; __first != __last; ++__first)
			push_back(*__first);
	}

	template <typename _Tp, typename _Allocator>
	template <typename _ForwardIterator>
	vector<_Tp, _Allocator>::vector(_ForwardIterator __first,
									typename enable_if<__is_forward_iterator<_ForwardIterator>::value,
													   _ForwardIterator>::type __last,
									const allocator_type &alloc) : __base(alloc)
	{
		size_type __n = static_cast<size_type>(ft::distance(__first, __last));
		if (__n > 0)
		{
			this->__allocate_memory(__n); // allocate memory
			std::uninitialized_copy(__first, __last, this->__end_);
			this->__end_ = this->__begin_ + __n;
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

	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::resize(size_type __sz)
	{
		size_type __current = size();
		if (__current < __sz) // Expand and insert
			this->__append(__sz - __current);
		else if (__current > __sz)
			this->__destruct_at_end(this->__begin_ + __sz);
	}

	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x)
	{
		size_type __current = size();
		if (__current < __sz) // Expand and insert
			this->__append(__sz - __current, __x);
		else if (__current > __sz)
			this->__destruct_at_end(this->__begin_ + __sz);
	}

	// --*-- Modifiers --*--
	// 01. assign
	template <typename _Tp, typename _Allocator>
	template <typename _InputIterator>
	typename enable_if<__is_input_iterator<_InputIterator>::value &&
						   !__is_forward_iterator<_InputIterator>::value,
					   void>::type
	vector<_Tp, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
	{
		clear();
		for (; __first != __last; ++__first)
		{
			push_back(*__first);
		}
	}

	template <typename _Tp, typename _Allocator>
	template <typename _ForwardIterator>
	typename enable_if<
		__is_forward_iterator<_ForwardIterator>::value,
		void>::type
	vector<_Tp, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
	{
		if (this->__begin_ != nullptr)
		{
			clear();
			this->__alloc_.deallocate(this->__begin_, capacity());
			this->__begin_ = this->__end_ = this->__end_cap_ = nullptr;
		}
		difference_type __ns = ft::distance(__first, __last);
		const size_t __n = static_cast<size_type>(__ns);
		if (__n)
		{
			vector<_Tp, _Allocator> __tmp_(__n, value_type(), this->__alloc_);
			__tmp_.__end_ = std::uninitialized_copy(__first, __last, __tmp_.__begin_);
			swap(__tmp_);
		}
	}

	// 02. assign
	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::assign(size_type __n, const_reference __u)
	{
		if (__n <= capacity()) // No reallocation needed
		{
			size_type __s = size(); // get current size
			std::uninitialized_fill_n(this->__begin_, std::min(__n, __s), __u);
			if (__n > __s)
				this->__construct_at_end(__n - __s, __u);
			else
				this->__destruct_at_end(this->__begin_ + __n);
		}
		else // reallocation needed
		{
			this->__alloc_.deallocate(this->__begin_, capacity());
			this->__allocate_memory(static_cast<size_type>(__n));
			std::uninitialized_fill(this->__begin_, this->__begin_ + __n, __u);
			this->__end_ = this->__begin_ + __n;
		}
	}

	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::push_back(const_reference __x)
	{
		// add one element at the end of the vector
		if (this->__end_ != this->__end_cap_)
		{
			// No reallocation needed
			this->__alloc_.construct(this->__end_, __x); // construct one element
			++this->__end_;								 // set end point
		}
		else
		{
			const size_type __max_size = this->max_size(); // max_size
			size_type __capacity = this->capacity();	   // capacity
			size_type __new_size = __capacity > __max_size / 2 ? __max_size : __capacity * 2;
			if (__new_size == 0)
				__new_size = 1;
			reserve(__new_size);						 // request expand vector storage using reserve function
			this->__alloc_.construct(this->__end_, __x); // construct
			++this->__end_;								 // set end point
		}
	}

	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::pop_back(void)
	{
		this->__destruct_at_end(this->__end_ - 1);
	}

	// 01. insert - single element
	// insert an element in a specific location
	template <typename _Tp, typename _Allocator>
	typename vector<_Tp, _Allocator>::iterator vector<_Tp, _Allocator>::insert(iterator position, const value_type &val)
	{
		iterator __p = this->__begin_ + (position - begin()); // point
		if (this->__end_ < this->__end_cap_)
		{
			if (__p == this->end())
			{
				push_back(val);
				__p = this->end() - 1;
			}
			else // Specific location
			{
				pointer __old_last = this->__end_;
				pointer __p_ = this->__begin_ + (position - begin());
				while (__old_last != __p_)
				{
					this->__alloc_.construct(__old_last, *(__old_last - 1));
					this->__alloc_.destroy(__old_last - 1);
					--__old_last;
				}
				this->__alloc_.construct(__p_, val);
				this->__end_++;
			}
		}
		else // reallocation needed
		{
			vector<_Tp, _Allocator> __tmp_(this->capacity() + 1, value_type(), this->__alloc_);
			__tmp_.assign(this->begin(), position);
			__tmp_.push_back(val);
			__p = __tmp_.end() - 1;
			std::cout << "1" << std::endl;
			for (iterator it = position; it != this->end(); it++)
			{
				std::cout << "2" << std::endl;
				this->__alloc_.construct(__tmp_.__end_++, *it);
			}
			std::cout
				<< "3" << std::endl;
			swap(__tmp_);
		}
		return iterator(__p);
	}

	// 02. insert - fill
	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::insert(iterator position, size_type n, const value_type &val)
	{
		difference_type __diff = position - this->begin();
		if (this->size() + n > this->capacity()) // reallocation needed
		{
			reserve(this->size() + n); // reserve
		}
		pointer __p = this->__begin_ + __diff;
		pointer __old_last = this->__end_;
		while (__old_last != __p)
		{
			this->__alloc_.construct(__old_last + n, *(__old_last - 1));
			this->__alloc_.destroy(__old_last - 1);
			--__old_last;
		}
		std::uninitialized_fill(__p, __p + n, val);
		this->__end_ = this->__end_ + n;
	}

	// 03. insert - range
	template <typename _Tp, typename _Allocator>
	template <typename InputIterator>
	void vector<_Tp, _Allocator>::insert(iterator position, InputIterator first,
										 typename enable_if<__is_input_iterator<InputIterator>::value &&
																!__is_forward_iterator<InputIterator>::value,
															InputIterator>::type last)
	{
		difference_type __diff = position - this->begin();
		difference_type __gap = ft::distance(first, last);
		if (this->size() + __gap > this->capacity())
		{
			this->reserve(this->size() + __gap);
		}
		pointer __p = this->__begin_ + __diff;
		pointer __old_last = this->__end_;
		while (__old_last != __p)
		{
			this->__alloc_.construct(__old_last + __gap, *(__old_last - 1));
			this->__alloc_.destroy(__old_last - 1);
			--__old_last;
		}
		std::uninitialized_copy(first, last, __p);
		this->__end_ = this->__end_ + __gap;
	}

	template <typename _Tp, typename _Allocator>
	template <typename ForwardIterator>
	void vector<_Tp, _Allocator>::insert(iterator position, ForwardIterator first,
										 typename enable_if<__is_forward_iterator<ForwardIterator>::value,
															ForwardIterator>::type last)
	{
		difference_type __gap = ft::distance(first, last);
		difference_type __diff = position - this->begin();
		if (this->size() + __gap > this->capacity())
		{
			this->reserve(this->size() + __gap);
		}
		pointer __p = this->__begin_ + __diff;
		pointer __old_last = this->__end_;
		while (__old_last != __p)
		{
			--__old_last;
			this->__alloc_.construct(__old_last + __gap, *(__old_last));
			this->__alloc_.destroy(__old_last);
		}
		std::uninitialized_copy(first, last, __p);
		this->__end_ = this->__end_ + __gap;
	}

	// swap
	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::swap(vector &x)
	{
		// tmp
		pointer tmp_beg = this->__begin_;
		pointer tmp_end = this->__end_;
		pointer tmp_cap = this->__end_cap_;
		allocator_type tmp_all = this->__alloc_;
		// this
		this->__begin_ = x.__begin_;
		this->__end_ = x.__end_;
		this->__end_cap_ = x.__end_cap_;
		this->__alloc_ = x.__alloc_;
		// x
		x.__begin_ = tmp_beg;
		x.__end_ = tmp_end;
		x.__end_cap_ = tmp_cap;
		x.__alloc_ = tmp_all;
	}

	template <typename _Tp, typename _Allocator>
	void vector<_Tp, _Allocator>::clear()
	{
		this->__clear();
	}

	// --*-- NON - MEMBER FUNCTION (friend operation) --*--

} // namespace ft

#endif