/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:28:57 by mcha              #+#    #+#             */
/*   Updated: 2022/08/15 20:36:16 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rbtree.hpp"

namespace ft
{
	// *--*--*--*--*--*--*--*--*--*--*--*--
	// Increment
	static _rb_tree_node_base *
	local_rb_tree_increment(_rb_tree_node_base *__x) throw()
	{
		if (__x->_m_right != 0)
		{
			__x = __x->_m_right;
			while (__x->_m_left != 0)
				__x = __x->_m_left;
		}
		else
		{
			_rb_tree_node_base *__y = __x->_m_parent;
			while (__x == __y->_m_right)
			{
				__x = __y;
				__y = __y->_m_parent;
			}
			if (__x->_m_right != __y)
				__x = __y;
		}
		return __x;
	}

	_rb_tree_node_base *
	_rb_tree_increment(_rb_tree_node_base *__x) ___NOEXCEPT__
	{
		return local_rb_tree_increment(__x);
	}

	const _rb_tree_node_base *
	_rb_tree_increment(const _rb_tree_node_base *__x) ___NOEXCEPT__
	{
		return local_rb_tree_increment(const_cast<_rb_tree_node_base *>(__x));
	}

	// *--*--*--*--*--*--*--*--*--*--*--*--
	// Decrement

	static _rb_tree_node_base *
	local_rb_tree_decrement(_rb_tree_node_base *__x) throw()
	{
		if (__x->_m_color == _s_red && __x->_m_parent->_m_parent == __x)
			__x = __x->_m_right;
		else if (__x->_m_left != 0)
		{
			_rb_tree_node_base *__y = __x->_m_left;
			while (__y->_m_right != 0)
				__y = __y->_m_right;
			__x = __y;
		}
		else
		{
			_rb_tree_node_base *__y = __x->_m_parent;
			while (__x == __y->_m_left)
			{
				__x = __y;
				__y = __y->_m_parent;
			}
			__x = __y;
		}
		return __x;
	}

	_rb_tree_node_base *
	_rb_tree_decrement(_rb_tree_node_base *__x) throw()
	{
		return local_rb_tree_decrement(__x);
	}

	const _rb_tree_node_base *
	_rb_tree_decrement(const _rb_tree_node_base *__x) throw()
	{
		return local_rb_tree_decrement(const_cast<_rb_tree_node_base *>(__x));
	}

	void _rb_tree_insert_and_rebalance(const bool __insert_left,
									   _rb_tree_node_base *__x,
									   _rb_tree_node_base *__p,
									   _rb_tree_node_base &__header) ___NOEXCEPT__
	{
		// Keep root
		_rb_tree_node_base *&__root = __header._m_parent;

		// Initialize fields in new node to insert
		// __x is new node
		__x->_m_parent = __p;
		__x->_m_left = 0;
		__x->_m_right = 0;
		__x->_m_color = _s_red;

		// Insert
		if (__insert_left) // First node is always inserted left
		{
			__p->_m_left = __x; // Insert at left

			if (__p == &__header) // No node in tree
			{
				__header._m_parent = __x;
				__header._m_right = __x;
			}
			else if (__p == __header._m_left)
				__header._m_left = __x; // If p is leftmost, __x is leftmost
		}
		else // Right insert
		{
			__p->_m_right = __x;

			if (__p == __header._m_right) // If p is rightmost, __x is rightmost
				__header._m_right = __x;
		}
	}
}
