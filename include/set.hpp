/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:35:05 by mcha              #+#    #+#             */
/*   Updated: 2022/08/22 22:04:53 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

// --*-- Define --*--
#define ___NOEXCEPT__ throw()

// --*-- Include --*--
#include <functional>
#include <memory>

#include "rbtree.hpp"
#include "utility.hpp"

namespace ft
{
	template <typename _Key, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<_Key> >
	class set
	{
		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// public typedef
	public:
		typedef _Key key_type;	 // 1.
		typedef _Key value_type; // 2. Why 'Key' defined twice?
		typedef _Compare key_compare;
		typedef _Compare value_compare;
		typedef _Alloc allocator_type;

	private:
		typedef typename _Alloc::template rebind<_Key>::other _key_alloc_type;
		typedef _rb_tree<key_type, value_type, _Identity<value_type>, key_compare, _key_alloc_type> __base;

		__base __tree; // red-black tree

	public:
		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// iterator related typedefs
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
	};

} // namespace ft

#endif