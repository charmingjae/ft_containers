/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:25:24 by mcha              #+#    #+#             */
/*   Updated: 2022/08/22 22:03:01 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "type_traits.hpp"

namespace ft
{
	template <typename _T1, typename _T2>
	struct pair
	{
		typedef _T1 first_type;
		typedef _T2 second_type;

		_T1 first;
		_T2 second;

		// --*-- 1. default constructor --*--
		// pair()
		pair() : first(), second() {}

		// --*-- 2. copy constructor --*--
		// template<class U, class V> pair (const pair<U,V>& pr);
		template <typename _U1, typename _U2>
		pair(const pair<_U1, _U2> &__p) : first(__p.first), second(__p.second) {}

		// --*-- 3. initialization constructor --*--
		// pair (const first_type& a, const second_type& b);
		pair(_T1 const &__t1, _T2 const &__t2) : first(__t1), second(__t2) {}

		// --*-- operator= --*--
		pair &operator=(pair const &__p)
		{
			first = __p.first;
			second = __p.second;
			return *this;
		}
	};

	// --*-- Non member operator --*--
	template <typename _T1, typename _T2>
	bool operator==(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return __x.first == __y.first && __x.second == __y.second;
	}

	template <class _T1, class _T2>
	bool operator!=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return !(__x == __y);
	}

	template <class _T1, class _T2>
	bool operator<(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return __x.first < __y.first ||
			   (!(__y.first < __x.first) && __x.second < __y.second);
	}

	template <class _T1, class _T2>
	bool operator>(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return __y < __x;
	}

	template <class _T1, class _T2>
	bool operator>=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return !(__x < __y);
	}

	template <class _T1, class _T2>
	bool operator<=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
	{
		return !(__y < __x);
	}

	// --*-- Make pair --*--
	template <class _T1, class _T2>
	pair<_T1, _T2> make_pair(_T1 __x, _T2 __y)
	{
		return pair<_T1, _T2>(__x, __y);
	}

	template <typename T>
	void swap(T &x, T &y)
	{
		T tmp(x);
		x = y;
		y = tmp;
	}

	// --*-- Select 1st --*--
	template <typename _Pair>
	struct _Select1st
	{
		typename _Pair::first_type &operator()(_Pair &__x) const { return __x.first; }

		const typename _Pair::first_type &operator()(const _Pair &__x) const
		{
			return __x.first;
		}
	};

	// --*-- Identity --*--
	template <typename _Tp>
	struct _Identity
	{
		_Tp &operator()(_Tp &__x) const
		{
			return __x;
		}

		const _Tp &operator()(const _Tp &__x) const
		{
			return __x;
		}
	};

	// --*-- _Identity specialization --*--
	template <typename _Tp>
	struct _Identity<const _Tp> : _Identity<_Tp>
	{
	};

} // namespace ft

#endif