/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:50:55 by mcha              #+#    #+#             */
/*   Updated: 2022/08/15 17:28:49 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

// --*--*--*--*--*--*--
// Define
#define ___NOEXCEPT__ throw()

// --*--*--*--*--*--*--
// Include
#include <cstddef>

namespace ft
{
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Node color
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	enum _rb_tree_color
	{
		_s_red = false,
		_s_black = true
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Tree base
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	struct _rb_tree_node_base
	{
		// --*--*--*--*--*--*--
		// Typedef
		typedef _rb_tree_node_base *_base_ptr;
		typedef const _rb_tree_node_base *_const_base_ptr;

		// --*--*--*--*--*--*--
		// Member
		_rb_tree_color _m_color;
		_base_ptr _m_parent;
		_base_ptr _m_left;
		_base_ptr _m_right;

		// --*--*--*--*--*--*--
		// Explore
		static _base_ptr
		_s_minimum(_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->_m_left != 0)
				__x = __x->_m_left;
			return __x;
		}

		static _const_base_ptr
		_s_minimum(_const_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->_m_left != 0)
				__x = __x->_m_left;
			return __x;
		}

		static _base_ptr
		_s_maximum(_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->_m_right != 0)
				__x = __x->_m_right;
			return __x;
		}

		static _const_base_ptr
		_s_maximum(_const_base_ptr __x) ___NOEXCEPT__
		{
			while (__x->_m_right != 0)
				__x = __x->_m_right;
			return __x;
		}
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Key compare functor
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _key_compare>
	struct _rb_tree_key_compare
	{
		_key_compare _m_key_compare;

		_rb_tree_key_compare() ___NOEXCEPT__ : _m_key_compare() {}
		_rb_tree_key_compare(const _key_compare &__comp) : _m_key_compare(__comp) {}
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Tree initialization helper
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	struct _rb_tree_header
	{
		_rb_tree_node_base _m_header;
		size_t _m_node_count; // Tracking size of tree

		void _m_reset()
		{
			_m_header._m_parent = 0;
			_m_header._m_left = &_m_header;
			_m_header._m_right = &_m_header;
			_m_node_count = 0;
		}

		_rb_tree_header() ___NOEXCEPT__
		{
			_m_header._m_color = _s_red; // Set default node color as RED
			_m_reset();
		}

		void _m_move_data(_rb_tree_header &__from)
		{
			_m_header._m_color = __from._m_header._m_color;
			_m_header._m_parent = __from._m_header._m_parent;
			_m_header._m_left = __from._m_header._m_left;
			_m_header._m_right = __from._m_header._m_right;
			_m_header._m_parent->_m_parent = &_m_header;
			_m_node_count = __from._m_node_count;

			__from._M_reset();
		}
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Tree node
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _value>
	struct _rb_tree_node : public _rb_tree_node_base
	{
		typedef _rb_tree_node<_value> *_link_type;

		_value _m_value_field;

		_value *_m_valptr() { return &_m_value_field; }
		const _value *_m_valptr() const { return &_m_value_field; }
	};

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// EXAMPLE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
}

#endif
