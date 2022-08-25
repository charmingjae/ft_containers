/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:35:05 by mcha              #+#    #+#             */
/*   Updated: 2022/08/25 17:24:18 by mcha             ###   ########.fr       */
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
		// Can modification of keys
		typedef typename __base::const_iterator iterator;
		typedef typename __base::const_iterator const_iterator;
		typedef typename __base::const_reverse_iterator reverse_iterator;
		typedef typename __base::const_reverse_iterator const_reverse_iterator;
		typedef typename __base::size_type size_type;
		typedef typename __base::difference_type difference_type;

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Constructor
		set() : __tree() {}
		explicit set(const _Compare &__comp, const allocator_type &__a = allocator_type())
			: __tree(__comp, _key_alloc_type(__a)) {}

		template <typename _InputIterator>
		set(_InputIterator __first, _InputIterator __last) : __tree()
		{
			__tree.__insert_range_unique(__first, __last);
		}

		template <typename _InputIterator>
		set(_InputIterator __first, _InputIterator __last, const _Compare &__comp, const allocator_type &__a = allocator_type())
			: __tree(__comp, _key_alloc_type(__a))
		{
			__tree.__insert_range_unique(__first, __last);
		}

		set(const set &__x)
			: __tree(__x.__tree)
		{
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Assignment operator
		set &operator=(const set &__x)
		{
			__tree = __x.__tree;
			return *this;
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Accessors

		/// Returns the comparison object with which the set was constructed
		key_compare key_comp() const
		{
			return __tree.key_comp();
		}
		/// Returns the comparison object with which the set was constructed
		value_compare value_comp() const
		{
			return __tree.key_comp();
		}
		/// Returns the allocator object
		allocator_type get_allocator() const ___NOEXCEPT__
		{
			return allocator_type(__tree.get_allocator());
		}
		/// Returns a read-only (constant) iterator that points to the first element in the set.
		iterator begin() const ___NOEXCEPT__
		{
			return __tree.begin();
		}

		iterator end() const ___NOEXCEPT__
		{
			return __tree.end();
		}

		reverse_iterator rbegin() const ___NOEXCEPT__
		{
			return __tree.rbegin();
		}

		reverse_iterator rend() const ___NOEXCEPT__
		{
			return __tree.rend();
		}

		bool empty() const ___NOEXCEPT__
		{
			return __tree.empty();
		}

		size_type size() const ___NOEXCEPT__
		{
			return __tree.size();
		}

		size_type max_size() const ___NOEXCEPT__
		{
			return __tree.max_size();
		}

		void swap(set &__x) ___NOEXCEPT__
		{
			__tree.swap(__x.__tree);
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Insert
		/// Pair's first : first element is an iterator that points to the possibly inserted element
		/// Pair's second : is a bool that is true if the element was actually inserted
		ft::pair<iterator, bool> insert(const value_type &__x)
		{
			ft::pair<typename __base::iterator, bool> __p = __tree.__insert_unique(__x);
			return ft::pair<iterator, bool>(__p.first, __p.second);
		}

		// First : is only a hint and can potentially improve the performance of the insertion process
		iterator insert(const_iterator __position, const value_type &__x)
		{
			return __tree.__insert_unique_hint_pos(__position, __x);
		}

		template <typename _InputIterator>
		void insert(_InputIterator __first, _InputIterator __last)
		{
			__tree.__insert_range_unique(__first, __last);
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Erase
		void erase(iterator __position)
		{
			__tree.erase(__position);
		}

		size_type erase(const key_type &__x)
		{
			return __tree.erase(__x);
		}

		void erase(iterator __first, iterator __last)
		{
			__tree.erase(__first, __last);
		}

		void clear() ___NOEXCEPT__
		{
			__tree.clear();
		}

		size_type count(const key_type &__x) const
		{
			return __tree.find(__x) == __tree.end() ? 0 : 1;
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// Find
		/**
		 * @brief Tries to locate an element in a %set
		 *
		 * @param __x Element to be located
		 * @return iterator pointing to sought-after element, or end() if not found.
		 *
		 * Takes a key and tries to locate the element with which the key matches.
		 * If successful the function returns an iterator pointing to the sought after element.
		 * If unsuccessful it returns the past-the-end iterator.
		 */
		iterator find(const key_type &__x)
		{
			return __tree.find(__x);
		}

		const_iterator find(const key_type &__x) const
		{
			return __tree.find(__x);
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// lower_bound
		/**
		 * @brief Finds the beginning of a subsequence matching given key.
		 *
		 * @param __x Key that to be located.
		 * @return iterator pointing to first element equal to or greater than key, or end().
		 *
		 * This function returns the first element of a subsequence of elements that matches the given key.
		 * If unsuccessful it returns an iterator pointing to the first element that has a greater value
		 * than given key or end() if no such element exists.
		 */
		iterator lower_bound(const key_type &__x)
		{
			return __tree.lower_bound(__x);
		}

		const_iterator lower_bound(const key_type &__x) const
		{
			return __tree.lower_bound(__x);
		}

		// *==*==*==*==*==*==*==*==*==*==*==*==*
		// upper_bound
		/**
		 * @brief Finds the end of a subsequence matching given key.
		 *
		 * @param __x Key that to be located.
		 * @return iterator pointing to the first element greater than key, or end().
		 */
		iterator upper_bound(const key_type &__x)
		{
			return __tree.upper_bound(__x);
		}

		const_iterator upper_bound(const key_type &__x) const
		{
			return __tree.upper_bound(__x);
		}

		/**
		 * @brief Finds a subsequence matching given key
		 *
		 * @param __x Key to be located
		 * @return ft::pair<iterator, iterator> Pair of iterators that possibly points to the subsequence
		 * 			matching given key.
		 */
		ft::pair<iterator, iterator> equal_range(const key_type &__x)
		{
			return __tree.equal_range(__x);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &__x) const
		{
			return __tree.equal_range(__x);
		}
	};

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator==(const ft::set<_Key, _Compare, _Alloc> &__x,
					const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		// return __x.__tree == __y.__tree;
		return (__x.size() == __y.size() &&
				ft::equal(__x.begin(), __x.end(), __y.begin()));
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator<(const ft::set<_Key, _Compare, _Alloc> &__x,
				   const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		// return __x.__tree < __y.__tree;
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
										   __y.end());
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator!=(const ft::set<_Key, _Compare, _Alloc> &__x,
					const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator>(const ft::set<_Key, _Compare, _Alloc> &__x,
				   const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator<=(const ft::set<_Key, _Compare, _Alloc> &__x,
					const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	bool operator>=(const ft::set<_Key, _Compare, _Alloc> &__x,
					const ft::set<_Key, _Compare, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Key, typename _Compare, typename _Alloc>
	void swap(ft::set<_Key, _Compare, _Alloc> &__x, ft::set<_Key, _Compare, _Alloc> &__y) ___NOEXCEPT__
	{
		__x.swap(__y);
	}
} // namespace ft

#endif