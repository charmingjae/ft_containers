/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:55:35 by mcha              #+#    #+#             */
/*   Updated: 2022/08/17 20:38:03 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

// *--*--*--*--*--*--*--*--*--*--*
// Define

// *--*--*--*--*--*--*--*--*--*--*
// Include
#include "rbtree.hpp"
#include "utility.hpp"

namespace ft
{
	// =================================================================================================
	// map
	// =================================================================================================
	template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
			  typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
	class map
	{
		// *--*--*--*--*--*--*--*--*--*--*
		// Type define
	public:
		typedef _Key key_type;
		typedef _Tp mapped_type;
		typedef ft::pair<const _Key, _Tp> value_type;
		typedef _Compare key_compare;
		typedef _Alloc allocator_type;

	private:
		typedef typename _Alloc::template rebind<value_type>::other _pair_alloc_type;
		typedef _rb_tree<key_type, value_type, /* key of compare */ ft::_Select1st<value_type>, key_compare, allocator_type> __base;

	public:
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename __base::iterator iterator;
		typedef typename __base::const_iterator const_iterator;
		typedef typename __base::size_type size_type;
		typedef typename __base::difference_type difference_type;
		typedef typename __base::reverse_iterator reverse_iterator;
		typedef typename __base::const_reverse_iterator const_reverse_iterator;

	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<_Key, _Tp, _Compare, _Alloc>;

		protected:
			_Compare comp;
			value_compare(_Compare __c) : comp(__c) {}

		public:
			bool operator()(const value_type &__x, const value_type &__y) const
			{
				return comp(__x.first, __y.first);
			}
		};

	private:
		__base __tree; // The actual tree structure

	public:
		// *==*==*==*==*==*==*==*==*==*==*==
		// Constructor
		map() : __base() {}

		// __comp: A comparison object
		// __a: An allocator object
		explicit map(const _Compare &__comp, const allocator_type &__a = allocator_type())
			: __base(__comp, __a) {}

		// Map copy constructor
		map(const map &__x) : __base(__x.__tree) {}

		template <typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last) : __base()
		{
			__base.__insert_range_unique(__first, __last);
		}
	};
}

#endif