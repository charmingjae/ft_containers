/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:40:29 by mcha              #+#    #+#             */
/*   Updated: 2022/08/04 21:41:18 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

// --*-- Define --*--
#define _NOEXCEPT throw()

// --*-- Include --*--
#include "type_traits.hpp"
#include <cstddef>

namespace ft
{
	// --*-- Iterator tag --*--
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	// --*-- Iterator --*--
	template <typename Category,			 // iterator::iterator_category
			  typename T,					 // iterator::value_type
			  typename Distance = ptrdiff_t, // iterator::difference_type
			  typename Pointer = T *,		 // iterator::pointer
			  typename Reference = T &		 // iterator::reference
			  >
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	// --*-- Iterator traits [ Iterator, T *, T & ] --*--
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	// template <typename T>
	// struct iterator_traits<T *>
	// {
	// 	typedef ptrdiff_t difference_type;
	// 	typedef T value_type;
	// 	typedef T *pointer;
	// 	typedef T &reference;
	// 	typedef random_access_iterator_tag iterator_category;
	// };

	// template <typename T>
	// struct iterator_traits<const T *>
	// {
	// 	typedef ptrdiff_t difference_type;
	// 	typedef T value_type;
	// 	typedef const T *pointer;
	// 	typedef const T &reference;
	// 	typedef random_access_iterator_tag iterator_category;
	// };

	// --*-- Checker --*--
	// * 1. is iterator type is defined?
	template <typename _Tp>
	struct __has_iterator_typedefs
	{
	private:
		struct __two
		{
			char __lx;
			char __lxx;
		};
		template <class _Up>
		static __two __test(...);
		template <class _Up>
		static char __test(typename ft::__void_t<typename _Up::iterator_category>::type * = 0,
						   typename ft::__void_t<typename _Up::difference_type>::type * = 0,
						   typename ft::__void_t<typename _Up::value_type>::type * = 0,
						   typename ft::__void_t<typename _Up::reference>::type * = 0,
						   typename ft::__void_t<typename _Up::pointer>::type * = 0);

	public:
		static const bool value = sizeof(__test<_Tp>(0, 0, 0, 0, 0)) == 1;
	};

	// // * 2. is iterator category exists
	template <typename _Tp>
	struct __has_iterator_category
	{
	private:
		struct __two
		{
			char __lx;
			char __lxx;
		};
		template <typename _Up>
		static __two __test(...);

		template <typename _Up>
		static char __test(typename _Up::iterator_category * = 0);

	public:
		static const bool value = sizeof(__test<_Tp>(0)) == 1;
	};

	// --*-- iterator_traits implementation --*--
	template <typename _Iter, bool>
	struct __iterator_traits_impl
	{
	};

	template <typename _Iter>
	struct __iterator_traits_impl<_Iter, true>
	{
		typedef typename _Iter::difference_type difference_type;
		typedef typename _Iter::value_type value_type;
		typedef typename _Iter::pointer pointer;
		typedef typename _Iter::reference reference;
		typedef typename _Iter::iterator_category iterator_category;
	};

	template <typename _Iter, bool>
	struct __iterator_traits
	{
	};

	template <typename _Iter>
	struct __iterator_traits<_Iter, true> : __iterator_traits_impl<
												_Iter,
												is_same<typename _Iter::iterator_categroy, input_iterator_tag>::value ||
													is_same<typename _Iter::iterator_category, output_iterator_tag>::value ||
													is_same<typename _Iter::iterator_category, forward_iterator_tag>::value ||
													is_same<typename _Iter::iterator_category, bidirectional_iterator_tag>::value ||
													is_same<typename _Iter::iterator_category, random_access_iterator_tag>::value>
	{
	};

	template <typename _Tp>
	struct iterator_traits<_Tp *>
	{
		typedef ptrdiff_t difference_type;
		typedef typename ft::remove_cv<_Tp>::type value_type;
		typedef _Tp *pointer;
		typedef _Tp &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename _Tp>
	struct iterator_traits<const _Tp *>
	{
		typedef ptrdiff_t difference_type;
		typedef typename ft::remove_cv<_Tp>::type value_type;
		typedef const _Tp *pointer;
		typedef const _Tp &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	// --*-- reverse iterator --*--
	template <typename _Iter>
	class reverse_iterator : public iterator<typename iterator_traits<_Iter>::iterator_category,
											 typename iterator_traits<_Iter>::value_type,
											 typename iterator_traits<_Iter>::difference_type,
											 typename iterator_traits<_Iter>::pointer,
											 typename iterator_traits<_Iter>::reference>

	{
	private:
		_Iter __t;

	protected:
		_Iter current;

	public:
		typedef _Iter iterator_type;
		typedef typename iterator_traits<_Iter>::difference_type difference_type;
		typedef typename iterator_traits<_Iter>::reference reference;
		typedef typename iterator_traits<_Iter>::pointer pointer;

		// --*-- Constructor --*--
		reverse_iterator();
		explicit reverse_iterator(_Iter __x);
		template <typename _Up>
		reverse_iterator(const reverse_iterator<_Up> &__u);

		// --*-- Operation --*--
		template <typename _Up>
		reverse_iterator &operator=(const reverse_iterator<_Up> &__u);
		reference operator*(void) const;
		pointer operator->(void) const;
		reverse_iterator &operator++(void);
		reverse_iterator operator++(int);
		reverse_iterator &operator--(void);
		reverse_iterator operator--(int);
		reverse_iterator operator+(difference_type __n) const;
		reverse_iterator &operator+=(difference_type __n);
		reverse_iterator operator-(difference_type __n) const;
		reverse_iterator &operator-=(difference_type __n);
		reference operator[](difference_type __n) const;

		// --*-- Member function --*--
		_Iter base(void) const;
	};

	// --*-- Constructor implementation --*--
	template <typename _Iter>
	reverse_iterator<_Iter>::reverse_iterator() : __t(), current() {}

	template <typename _Iter>
	reverse_iterator<_Iter>::reverse_iterator(_Iter __x) : __t(__x), current(__x) {}

	template <typename _Iter>
	template <typename _Up>
	reverse_iterator<_Iter>::reverse_iterator(const reverse_iterator<_Up> &__u) : __t(__u.base()), current(__u.base()) {}

	// --*-- Operation --*--
	template <typename _Iter>
	template <typename _Up>
	reverse_iterator<_Iter> &reverse_iterator<_Iter>::operator=(const reverse_iterator<_Up> &__u)
	{
		__t = current = __u.base();
		return *this;
	}

	template <typename _Iter>
	typename reverse_iterator<_Iter>::reference reverse_iterator<_Iter>::operator*() const
	{
		_Iter __tmp = current;
		return *--__tmp;
	}

	template <typename _Iter>
	typename reverse_iterator<_Iter>::pointer reverse_iterator<_Iter>::operator->() const
	{
		return &(operator*());
	}

	template <typename _Iter>
	reverse_iterator<_Iter> &reverse_iterator<_Iter>::operator++()
	{
		--current;
		return *this;
	}

	template <typename _Iter>
	reverse_iterator<_Iter> reverse_iterator<_Iter>::operator++(int)
	{
		reverse_iterator __tmp(*this);
		--current;
		return __tmp;
	}

	template <typename _Iter>
	reverse_iterator<_Iter> &reverse_iterator<_Iter>::operator--()
	{
		++current;
		return *this;
	}

	template <typename _Iter>
	reverse_iterator<_Iter> reverse_iterator<_Iter>::operator--(int)
	{
		reverse_iterator __tmp(*this);
		++current;
		return __tmp;
	}

	template <typename _Iter>
	reverse_iterator<_Iter> reverse_iterator<_Iter>::operator+(difference_type __n) const
	{
		return reverse_iterator(current - __n);
	}

	template <typename _Iter>
	reverse_iterator<_Iter> &reverse_iterator<_Iter>::operator+=(difference_type __n)
	{
		current -= __n;
		return *this;
	}

	template <typename _Iter>
	reverse_iterator<_Iter> reverse_iterator<_Iter>::operator-(difference_type __n) const
	{
		return reverse_iterator(current + __n);
	}

	template <typename _Iter>
	reverse_iterator<_Iter> &reverse_iterator<_Iter>::operator-=(difference_type __n)
	{
		current += __n;
		return *this;
	}

	template <typename _Iter>
	typename reverse_iterator<_Iter>::reference reverse_iterator<_Iter>::operator[](difference_type __n) const
	{
		return *(*this + __n);
	}

	// --*-- Member function --*--
	template <typename _Iter>
	_Iter reverse_iterator<_Iter>::base(void) const
	{
		return current;
	}

	// --*-- Common operation --*--
	template <class _Iter1, class _Iter2>
	bool operator==(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() == __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator<(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() > __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator!=(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() != __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator>(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() < __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator>=(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() <= __y.base();
	}

	template <class _Iter1, class _Iter2>
	bool operator<=(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() >= __y.base();
	}

	template <class _Iter1, class _Iter2>
	typename reverse_iterator<_Iter1>::difference_type operator-(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __y.base() - __x.base();
	}

	template <class _Iter>
	reverse_iterator<_Iter> operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter> &__x)
	{
		return reverse_iterator<_Iter>(__x.base() - __n);
	}

	// --*-- function --*--
	template <typename _InputIter>
	typename iterator_traits<_InputIter>::difference_type
	__distance(_InputIter __first, _InputIter __last, input_iterator_tag)
	{
		typename iterator_traits<_InputIter>::difference_type __r(0);
		for (; __first != __last; ++__first)
			++__r;
		return __r;
	}

	template <typename _RandIter>
	typename iterator_traits<_RandIter>::difference_type
	__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)
	{
		return __last - __first;
	}

	template <typename _InputIter>
	typename iterator_traits<_InputIter>::difference_type
	distance(_InputIter __first, _InputIter __last)
	{
		return ft::__distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
	}

} // namespace ft

#endif