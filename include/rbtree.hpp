/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:50:55 by mcha              #+#    #+#             */
/*   Updated: 2022/08/15 23:08:53 by mcha             ###   ########.fr       */
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
	// PROTOTYPE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*

	// *--*--*--*--*--*--*--*--*--*--*
	// Struct prototype
	struct _rb_tree_node_base;

	// *--*--*--*--*--*--*--*--*--*--*
	// Iterator increment prototype
	_rb_tree_node_base *_rb_tree_increment(_rb_tree_node_base *__x) throw();
	const _rb_tree_node_base *_rb_tree_increment(const _rb_tree_node_base *__x) throw();
	_rb_tree_node_base *_rb_tree_decrement(_rb_tree_node_base *__x) throw();
	const _rb_tree_node_base *_rb_tree_decrement(const _rb_tree_node_base *__x) throw();

	// *--*--*--*--*--*--*--*--*--*--*
	// Rebalance prototype
	void _rb_tree_insert_and_rebalance(const bool __insert_left,
									   _rb_tree_node_base *__x,
									   _rb_tree_node_base *__p,
									   _rb_tree_node_base &__header) throw();
	_rb_tree_node_base *_rb_tree_rebalance_for_erase(_rb_tree_node_base *const __z,
													 _rb_tree_node_base &__header) throw();

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

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor constructor
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

	template <typename _Value>
	struct _rb_tree_node : public _rb_tree_node_base
	{
		typedef _rb_tree_node<_Value> *_link_type;

		_Value __value_field;
		_Value *__valptr() { return &__value_field; }
		const _Value *__valptr() const { return &__value_field; }

	}; // End of _rb_tree_node

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Iterator
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _Tp>
	struct _rb_tree_iterator
	{
		typedef _Tp value_type;
		typedef _Tp &reference;
		typedef _Tp *pointer;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _rb_tree_iterator<_Tp> _self;
		typedef _rb_tree_node_base::_base_ptr _base_ptr;
		typedef _rb_tree_node<_Tp> *_link_type;

		_base_ptr __node;

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor constructor
		_rb_tree_iterator() ___NOEXCEPT__
			: __node() {}
		explicit _rb_tree_iterator(_base_ptr __x) ___NOEXCEPT__
			: __node(__x) {} // Set base ptr with __X

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor operator
		reference operator*() const ___NOEXCEPT__
		{
			return *static_cast<_link_type>(__node)->__valptr();
		}

		pointer operator->() const ___NOEXCEPT__
		{
			return static_cast<_link_type>(__node)->__valptr();
		}

		_self &operator++() ___NOEXCEPT__
		{
			__node = _rb_tree_increment(__node);
			return *this;
		}

		_self operator++(int) ___NOEXCEPT__
		{
			_self __tmp = *this;
			__node = _rb_tree_increment(__node);
			return __tmp;
		}

		_self &operator--() ___NOEXCEPT__
		{
			__node = _rb_tree_decrement(__node);
			return *this;
		}

		_self operator--(int) ___NOEXCEPT__
		{
			_self __tmp = *this;
			__node = _rb_tree_decrement(__node);
			return __tmp;
		}

		friend bool operator==(const _self &__x, const _self &__y) ___NOEXCEPT__
		{
			return __x.__node == __y.__node;
		}

		friend bool operator!=(const _self &__x, const _self &__y) ___NOEXCEPT__
		{
			return __x.__node != __y.__node;
		}
	}; // End of _rb_tree_iterator

	template <typename _Tp>
	struct _rb_tree_const_iterator
	{
		typedef _Tp value_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;

		typedef _rb_tree_iterator<_Tp> iterator; // normal iterator
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _rb_tree_iterator<_Tp> _self;
		typedef _rb_tree_node_base::_const_base_ptr _base_ptr;
		typedef const _rb_tree_node<_Tp> *_link_type;

		_base_ptr __node;

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor constructor
		_rb_tree_const_iterator() ___NOEXCEPT__
			: __node() {}
		explicit _rb_tree_const_iterator(_base_ptr __x) ___NOEXCEPT__
			: __node(__x) {} // Set base ptr with __X
		_rb_tree_const_iterator(const iterator &__it) ___NOEXCEPT__
			: __node(__it.__node) {} // Set base ptr with __it.__node

		// *--*--*--*--*--*--*--*--*--*--*
		// Wrap const cast
		iterator __const_cast() const ___NOEXCEPT__
		{
			return iterator(const_cast<typename iterator::_base_ptr>(__node));
		}

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor operator
		reference operator*() const ___NOEXCEPT__
		{
			return *static_cast<_link_type>(__node)->__valptr();
		}

		pointer operator->() const ___NOEXCEPT__
		{
			return static_cast<_link_type>(__node)->__valptr();
		}

		_self &operator++() ___NOEXCEPT__
		{
			__node = _rb_tree_increment(__node);
			return *this;
		}

		_self operator++(int) ___NOEXCEPT__
		{
			_self __tmp = *this;
			__node = _rb_tree_increment(__node);
			return __tmp;
		}

		_self &operator--() ___NOEXCEPT__
		{
			__node = _rb_tree_decrement(__node);
			return *this;
		}

		_self operator--(int) ___NOEXCEPT__
		{
			_self __tmp = *this;
			__node = _rb_tree_decrement(__node);
			return __tmp;
		}

		friend bool operator==(const _self &__x, const _self &__y) ___NOEXCEPT__
		{
			return __x.__node == __y.__node;
		}

		friend bool operator!=(const _self &__x, const _self &__y) ___NOEXCEPT__
		{
			return __x.__node != __y.__node;
		}
	}; // End of _rb_tree_const_iterator

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Red - Black tree
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc = std::allocator<_Value> >
	class _rb_tree
	{
		// allocator<_Value> other;
		typedef typename _Alloc::template rebind<_rb_tree_node<_Value> >::other _node_allocator;

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] type definition
	protected:
		typedef _rb_tree_node_base *_base_ptr;
		typedef const _rb_tree_node_base *_const_base_ptr;
		typedef _rb_tree_node<_Value> *_link_type;
		typedef const _rb_tree_node<_Value> *_const_link_type;

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Public ] type definition
	public:
		typedef _Key key_type;
		typedef _Value value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _Alloc allocator_type;

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] Member variable
	protected:
		_rb_tree_impl<_Compare> __impl; // node allocator?

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Public ] Function implementation
	public:
		_node_allocator &__get_node_allocator() ___NOEXCEPT__
		{
			return this->__impl;
		}

		const _node_allocator &__get_node_allocator() const ___NOEXCEPT__
		{
			return this->__impl;
		}

		allocator_type get_allocator() const ___NOEXCEPT__
		{
			return allocator_type(__get_node_allocator());
		}

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] Function implementation
	protected:
		_link_type __allocate_node()
		{
			return this->__get_node_allocator().allocate(1);
		}

		void __deallocate_node(_link_type __p) ___NOEXCEPT__
		{
			this->__get_node_allocator(__p, 1);
		}

		}; // Finally red - black 'class' is entrance

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// EXAMPLE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
}

#endif
