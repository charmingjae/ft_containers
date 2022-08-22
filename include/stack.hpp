/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:34:06 by mcha              #+#    #+#             */
/*   Updated: 2022/08/22 20:04:45 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

// --*-- Define --*--
#include "vector.hpp"

namespace ft
{
	template <typename _Tp, typename _Container = ft::vector<_Tp> >
	class stack
	{
	public:
		typedef _Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type size_type;

		// protected:
		// 	container_type c;
	public:
		container_type c;

	public:
		// --*-- Constructor --*--
		explicit stack(const container_type &__c) : c(__c) {}
		stack() ___NOEXCEPT__ : c() {}
		stack(const stack &__q) : c(__q.c) {}
		stack &operator=(const stack &__q)
		{
			c = __q.c;
			return *this;
		}

		// --*-- Member function --*--
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		void push(const value_type &__v) { c.push_back(__v); }
		void pop() { c.pop_back(); }
	};

	// --*-- Non member function --*--

	template <class _Tp, class _Container>
	bool operator==(const stack<_Tp, _Container> &__x,
					const stack<_Tp, _Container> &__y)
	{
		return __x.c == __y.c;
	}

	template <class _Tp, class _Container>
	bool operator<(const stack<_Tp, _Container> &__x,
				   const stack<_Tp, _Container> &__y)
	{
		return __x.c < __y.c;
	}

	template <class _Tp, class _Container>
	bool operator!=(const stack<_Tp, _Container> &__x,
					const stack<_Tp, _Container> &__y)
	{
		return !(__x == __y);
	}

	template <class _Tp, class _Container>
	bool operator>(const stack<_Tp, _Container> &__x,
				   const stack<_Tp, _Container> &__y)
	{
		return __y < __x;
	}

	template <class _Tp, class _Container>
	bool operator>=(const stack<_Tp, _Container> &__x,
					const stack<_Tp, _Container> &__y)
	{
		return !(__x < __y);
	}

	template <class _Tp, class _Container>
	bool operator<=(const stack<_Tp, _Container> &__x,
					const stack<_Tp, _Container> &__y)
	{
		return !(__y < __x);
	}
} // namespace ft

#endif