/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:55:35 by mcha              #+#    #+#             */
/*   Updated: 2022/08/18 01:06:02 by mcha             ###   ########.fr       */
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
#include <stdexcept>

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

		template <typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last, const _Compare &__comp, const allocator_type &__a = allocator_type())
			: __base(__comp, __a)
		{
			__base.__insert_range_unique(__first, __last);
		}

		map &operator=(const map &__x)
		{
			__base = __x.__base;
			return *this;
		}

		allocator_type get_allocator() const ___NOEXCEPT__
		{
			return allocator_type(__base.get_allocator());
		}

		iterator begin() ___NOEXCEPT__
		{
			return __base.begin();
		}

		const_iterator begin() const ___NOEXCEPT__
		{
			return __base.begin();
		}

		iterator end() ___NOEXCEPT__
		{
			return __base.end();
		}

		const_iterator end() const ___NOEXCEPT__
		{
			return __base.end();
		}

		reverse_iterator rbegin() ___NOEXCEPT__
		{
			return __base.rbegin();
		}

		const_reverse_iterator rbegin() const ___NOEXCEPT__
		{
			return __base.rbegin();
		}

		reverse_iterator rend() ___NOEXCEPT__
		{
			return __base.rend();
		}

		const_reverse_iterator rend() const ___NOEXCEPT__
		{
			return __base.rend();
		}

		bool empty() const ___NOEXCEPT__
		{
			return __base.empty();
		}

		size_type size() const ___NOEXCEPT__
		{
			return __base.size();
		}

		size_type max_size() const ___NOEXCEPT__
		{
			return __base.max_size();
		}

		mapped_type &operator[](const key_type &__k)
		{
			iterator __i = lower_bound(__k);
			// __i->first is greater than or equivalent to __k
			if (__i == end() || key_comp()(__k, (*__i).first))
				__i = insert(__i, value_type(__k, mapped_type()));
			return (*__i).second; // node's value
		}

		void __throw_out_of_range(const char *msg)
		{
			throw std::out_of_range(__msg);
		}

		mapped_type &at(const key_type &__k)
		{
			iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				__throw_out_of_range("map::at"); // throw;
			return (*__i).second;
		}

		const mapped_type &at(const key_type &__k) const
		{
			const_iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				__throw_out_of_range("map::at"); // throw;
			return (*__i).second;
		}

		ft::pair<iterator, bool> insert(const value_type &__x)
		{
			return __base.__insert_unique(__x); // Implementation needed
		}
	};
}

#endif