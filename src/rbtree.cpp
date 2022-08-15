/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:28:57 by mcha              #+#    #+#             */
/*   Updated: 2022/08/15 21:49:46 by mcha             ###   ########.fr       */
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
		if (__x->__right != 0)
		{
			__x = __x->__right;
			while (__x->__left != 0)
				__x = __x->__left;
		}
		else
		{
			_rb_tree_node_base *__y = __x->__parent;
			while (__x == __y->__right)
			{
				__x = __y;
				__y = __y->__parent;
			}
			if (__x->__right != __y)
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
		if (__x->__color == COLOR_RED && __x->__parent->__parent == __x)
			__x = __x->__right;
		else if (__x->__left != 0)
		{
			_rb_tree_node_base *__y = __x->__left;
			while (__y->__right != 0)
				__y = __y->__right;
			__x = __y;
		}
		else
		{
			_rb_tree_node_base *__y = __x->__parent;
			while (__x == __y->__left)
			{
				__x = __y;
				__y = __y->__parent;
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
}
