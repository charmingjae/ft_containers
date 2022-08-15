/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:50:55 by mcha              #+#    #+#             */
/*   Updated: 2022/08/15 21:40:16 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

// --*--*--*--*--*--*--
// Define
#define ___NOEXCEPT__ throw()

// --*--*--*--*--*--*--
// Include
#include <memory>
#include <cstddef>
#include "iterator.hpp"

namespace ft
{
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Node color
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	enum _rb_tree_color
	{
		COLOR_RED = false,
		COLOR_BLACK = true
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Rb tree node base
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	struct _rb_tree_node_base
	{
		typedef _rb_tree_node_base *_base_ptr;
		typedef const _rb_tree_node_base *_const_base_ptr;

		_rb_tree_color __color; // enum color
		_base_ptr __parent;		// parent node
		_base_ptr __left;		// left child node
		_base_ptr __right;		// right child node

		static _base_ptr _s_minimum(_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->__left != 0)
				__x = __x->__left;
			return __x;
		}

		static _const_base_ptr _s_minimum(_const_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->__left != 0)
				__x = __x->__left;
			return __x;
		}

		static _base_ptr _s_maximum(_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->__right != 0)
				__x = __x->__right;
			return __x;
		}

		static _const_base_ptr _s_maximum(_const_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->__right != 0)
				__x = __x->__right;
			return __x;
		}
	}; // End of _rb_tree_node_base structure

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Key compare
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _key_compare>
	struct _rb_tree_key_compare
	{
		_key_compare __key_compare; // Variable

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor constructor
		_rb_tree_key_compare() ___NOEXCEPT__
			: __key_compare()
		{
		}
		_rb_tree_key_compare(const _key_compare &__comp)
			: __key_compare(__comp) // Bind __key_compare with __comp
		{
		}

	}; // End of _rb_tree_key_compare

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Manage default initialization of node count and header
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	struct _rb_tree_header
	{
		_rb_tree_node_base __header; // header variable
		size_t __node_count;		 // Track of size of tree

		_rb_tree_header() ___NOEXCEPT__ // Functor constructor
		{
			__header.__color = COLOR_RED;
			__reset();
		}

		void __move_data(_rb_tree_header &__from)
		{
			// Move data __from -> __header
			__header.__color = __from.__header.__color;
			__header.__parent = __from.__header.__parent;
			__header.__left = __from.__header.__left;
			__header.__right = __from.__header.__right;
			__header.__parent->__parent = &__header;
			__node_count = __from.__node_count;

			__from.__reset(); // reset from
		}

		void __reset()
		{
			__header.__parent = 0;
			__header.__left = &__header;
			__header.__right = &__header;
			__node_count = 0;
		}
	}; // End of _rb_tree_header

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// EXAMPLE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
}

#endif
