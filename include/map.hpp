/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:55:35 by mcha              #+#    #+#             */
/*   Updated: 2022/08/25 17:33:13 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

// *--*--*--*--*--*--*--*--*--*--*
// Define
#define ___NOEXCEPT__ throw()

// *--*--*--*--*--*--*--*--*--*--*
// Include
#include <stdexcept>
#include <functional>

#include "algorithm.hpp"
#include "iterator"
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
		typedef _rb_tree<key_type, value_type,
						 /* key of compare */ ft::_Select1st<value_type>, key_compare,
						 allocator_type>
			__base;

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
		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			friend class map<_Key, _Tp, _Compare, _Alloc>; // To use protected member function

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

	protected:
		void __throw_out_of_range(const char *msg) { throw std::out_of_range(msg); }

	public:
		// *==*==*==*==*==*==*==*==*==*==*==
		// Constructor
		map() : __tree() {}

		// __comp: A comparison object
		// __a: An allocator object
		explicit map(const _Compare &__comp,
					 const allocator_type &__a = allocator_type())
			: __tree(__comp, __a) {}

		// Map copy constructor
		map(const map &__x) : __tree(__x.__tree) {}

		template <typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last) : __tree()
		{
			__tree.__insert_range_unique(__first, __last);
		}

		template <typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last, const _Compare &__comp,
			const allocator_type &__a = allocator_type())
			: __tree(__comp, __a)
		{
			__tree.__insert_range_unique(__first, __last);
		}

		map &operator=(const map &__x)
		{
			__tree = __x.__tree;
			return *this;
		}

		allocator_type get_allocator() const ___NOEXCEPT__
		{
			return allocator_type(__tree.get_allocator());
		}

		iterator begin() ___NOEXCEPT__ { return __tree.begin(); }

		const_iterator begin() const ___NOEXCEPT__ { return __tree.begin(); }

		iterator end() ___NOEXCEPT__ { return __tree.end(); }

		const_iterator end() const ___NOEXCEPT__ { return __tree.end(); }

		reverse_iterator rbegin() ___NOEXCEPT__ { return __tree.rbegin(); }

		const_reverse_iterator rbegin() const ___NOEXCEPT__
		{
			return __tree.rbegin();
		}

		reverse_iterator rend() ___NOEXCEPT__ { return __tree.rend(); }

		const_reverse_iterator rend() const ___NOEXCEPT__ { return __tree.rend(); }

		bool empty() const ___NOEXCEPT__ { return __tree.empty(); }

		size_type size() const ___NOEXCEPT__ { return __tree.size(); }

		size_type max_size() const ___NOEXCEPT__ { return __tree.max_size(); }

		mapped_type &operator[](const key_type &__k)
		{
			iterator __i = lower_bound(__k);
			// __i->first is greater than or equivalent to __k
			if (__i == end() || key_comp()(__k, (*__i).first))
				__i = insert(__i, value_type(__k, mapped_type()));
			return (*__i).second; // node's value
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

		// map insert
		ft::pair<iterator, bool> insert(const value_type &__x)
		{
			return __tree.__insert_unique(__x); // Implementation needed
		}

		iterator insert(iterator __position, const value_type &__x)
		{
			return __tree.__insert_unique_hint_pos(__position, __x); // use hint
		}

		template <typename _InputIterator>
		void insert(_InputIterator __first, _InputIterator __last)
		{
			__tree.__insert_range_unique(__first, __last);
		}

		// map erase
		void erase(iterator __position) { __tree.erase(__position); }

		size_type erase(const key_type &__x) { return __tree.erase(__x); }

		void erase(iterator __first, iterator __last)
		{
			__tree.erase(__first, __last);
		}

		void swap(map &__x) ___NOEXCEPT__ { __tree.swap(__x.__tree); }

		void clear() ___NOEXCEPT__ { __tree.clear(); }

		key_compare key_comp() const { return __tree.key_comp(); }

		value_compare value_comp() const { return value_compare(__tree.key_comp()); }

		iterator find(const key_type &__x) { return __tree.find(__x); }

		const_iterator find(const key_type &__x) const { return __tree.find(__x); }

		size_type count(const key_type &__x) const
		{
			return __tree.find(__x) == __tree.end() ? 0 : 1;
		}

		iterator lower_bound(const key_type &__x) { return __tree.lower_bound(__x); }

		const_iterator lower_bound(const key_type &__x) const
		{
			return __tree.lower_bound(__x);
		}

		iterator upper_bound(const key_type &__x) { return __tree.upper_bound(__x); }

		const_iterator upper_bound(const key_type &__x) const
		{
			return __tree.upper_bound(__x);
		}

		ft::pair<iterator, iterator> equal_range(const key_type &__x)
		{
			return __tree.equal_range(__x);
		}

		ft::pair<const_iterator, const_iterator> equal_range(
			const key_type &__x) const
		{
			return __tree.equal_range(__x);
		}
	};

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator==(const ft::map<_Key, _Tp, _Compare, _Alloc> &__x,
					const ft::map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		// return __x._M_t == __y._M_t;
		return (__x.size() == __y.size() &&
				ft::equal(__x.begin(), __x.end(), __y.begin()));
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<(const map<_Key, _Tp, _Compare, _Alloc> &__x,
				   const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		// return __x.__tree < __y.__tree;
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
										   __y.end());
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator!=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>(const map<_Key, _Tp, _Compare, _Alloc> &__x,
				   const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	void swap(map<_Key, _Tp, _Compare, _Alloc> &__x,
			  map<_Key, _Tp, _Compare, _Alloc> &__y) ___NOEXCEPT__
	{
		__x.swap(__y);
	}
} // namespace ft

#endif