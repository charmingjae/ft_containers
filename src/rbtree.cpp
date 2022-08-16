/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:28:57 by mcha              #+#    #+#             */
/*   Updated: 2022/08/16 18:09:49 by mcha             ###   ########.fr       */
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

	// Rotate
	static void local_rb_tree_rotate_left(_rb_tree_node_base *const __x,
										  _rb_tree_node_base *&__root)
	{
		_rb_tree_node_base *const __y = __x->__right; // parent's right node

		__x->__right = __y->__left; // Set parent's right node as __y's left
		if (__y->__left != 0)
			__y->__left->__parent = __x; // Move right's left node to left's right node
		__y->__parent = __x->__parent;

		if (__x == __root) // Set root
			__root = __y;
		else if (__x == __x->__parent->__left)
			__x->__parent->__left = __y;  // Set __x's root's left node
		else							  // If __x is parent's right node
			__x->__parent->__right = __y; // Set __x's root's right node
		__y->__left = __x;
		__x->__parent = __y;
	}

	static void local_rb_tree_rotate_right(_rb_tree_node_base *const __x, _rb_tree_node_base *&__root)
	{
		_rb_tree_node_base *const __y = __x->__left;

		__x->__left = __y->__right;
		if (__y->__right != 0)
			__y->__right->__parent = __x;
		__y->__parent = __x->__parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->__parent->__right)
			__x->__parent->__right = __y;
		else
			__x->__parent->__left = __y;
		__y->__right = __x;
		__x->__parent = __y;
	}

	// Rebalance
	_rb_tree_node_base *_rb_tree_rebalance_for_erase(_rb_tree_node_base *const __z,
													 _rb_tree_node_base &__header) ___NOEXCEPT__
	{
		_rb_tree_node_base *&__root = __header.__parent;
		_rb_tree_node_base *&__leftmost = __header.__left;
		_rb_tree_node_base *&__rightmost = __header.__right;
		_rb_tree_node_base *__y = __z;
		_rb_tree_node_base *__x = 0;
		_rb_tree_node_base *__x_parent = 0;

		// Check __z has child
		if (__y->__left == 0)		// __z has at most one non-null child. y == z.
			__x = __y->__right;		// __x might be null.
		else if (__y->__right == 0) // __z has exactly one non-null child. y == z.
			__x = __y->__left;		// __x is not null.
		else						// if __z's both child is not null
		{
			// __z has two non-null children. Set __y to __z's successor. __x might be null
			__y = __y->__right;
			while (__y->__left != 0)
				__y = __y->__left;
			__x = __y->__right;
		}

		if (__y != __z) // Relink y in place of z. y is z's successor
		{
			__z->__left->__parent = __y;
			__y->__left = __z->__left;
			if (__y != __z->__right)
			{
				__x_parent = __y->__parent;
				if (__x)
					__x->__parent = __y->__parent;
				__y->__parent->__left = __x; // __y must be a child of __left
				__y->__right = __z->__right;
				__z->__right->__parent = __y;
			}
			else
			{
				__x_parent = __y;
			}
			if (__root == __z)
				__root = __y;
			else if (__z->__parent->__left = __z)
				__z->__parent->__left = __y;
			else
				__z->__parent->__right = __y;
			__y->__parent = __z->__parent;
			ft::swap(__y->__color, __z->__color);
			__y = __z;
			// __y now points to node to be actually deleted
		}
		else // __y == __z
		{
			__x_parent = __y->__parent;
			if (__x)
				__x->__parent = __y->__parent;
			if (__root == __z)
				__root = __x;
			else if (__z->__parent->__left == __z)
				__z->__parent->__left = __x;
			else
				__z->__parent->__right = __x;
			if (__leftmost == __z)
			{
				if (__z->__right == 0) // __z->__left must be null also
					__leftmost = __z->__parent;
				// makes __leftmost == __header if __z == __root
				else
					__leftmost = _rb_tree_node_base::_s_minimum(__x);
			}
			if (__rightmost == __z)
			{
				if (__z->__left == 0)
					__rightmost = __z->__parent;
				else
					__rightmost = _rb_tree_node_base::_s_maximum(__x);
			}
		}
		// recoloring, rotate ..
		// __y = Will be deleted node
		// __x = Replace node
		if (__y->__color != COLOR_RED) // deleted node is not RED
		{
			while (__x != __root && (__x == 0 || __x->__color == COLOR_BLACK)) // until __x is black...
			{
				if (__x == __x_parent->__left)
				{
					_rb_tree_node_base *__w = __x_parent->__right;
					if (__w->__color == COLOR_RED) // #Case 2-4: if x's sibling is RED
					{
						__w->__color = COLOR_BLACK;					   // change sibling's color to BLACK
						__x_parent->__color = COLOR_RED;			   // change parent color to RED
						local_rb_tree_rotate_left(__x_parent, __root); // rotate
						__w = __x_parent->__right;					   // Set __w
					}
					if ((__w->__left == 0 ||
						 __w->__left->__color == COLOR_BLACK) &&
						(__w->__right == 0 ||
						 __w->__right->__color == COLOR_BLACK))
					{
						__w->__color = COLOR_RED;
						__x = __x_parent;
						__x_parent = __x_parent->__parent;
					}
					else
					{
						if (__w->__right == 0 || __w->__right->__color == COLOR_BLACK)
						{
							__w->__left->__color = COLOR_BLACK;
							__w->__color = COLOR_RED;
							local_rb_tree_rotate_right(__w, __root);
							__w = __x_parent->__right;
						}
						__w->__color = __x_parent->__color;
						__x_parent->__color = COLOR_BLACK;
						if (__w->__right)
							__w->__right->__color = COLOR_BLACK;
						local_rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
				else
				{
				}
			}
		}
	}
}
