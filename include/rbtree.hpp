/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:50:55 by mcha              #+#    #+#             */
/*   Updated: 2022/08/25 17:17:02 by mcha             ###   ########.fr       */
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
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"
namespace ft
{
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// PROTOTYPE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*

	// *--*--*--*--*--*--*--*--*--*--*
	// Struct prototype
	struct _rb_tree_node_base;
	struct _rb_tree_impl;

	// *--*--*--*--*--*--*--*--*--*--*
	// Iterator increment prototype
	_rb_tree_node_base *_rb_tree_increment(_rb_tree_node_base *__x) throw();
	const _rb_tree_node_base *_rb_tree_increment(
		const _rb_tree_node_base *__x) throw();
	_rb_tree_node_base *_rb_tree_decrement(_rb_tree_node_base *__x) throw();
	const _rb_tree_node_base *_rb_tree_decrement(
		const _rb_tree_node_base *__x) throw();

	// *--*--*--*--*--*--*--*--*--*--*
	// Rebalance prototype
	void _rb_tree_insert_and_rebalance(const bool __insert_left,
									   _rb_tree_node_base *__x,
									   _rb_tree_node_base *__p,
									   _rb_tree_node_base &__header) throw();
	_rb_tree_node_base *_rb_tree_rebalance_for_erase(
		_rb_tree_node_base *const __z, _rb_tree_node_base &__header) throw();

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
		_rb_tree_key_compare() ___NOEXCEPT__ : __key_compare() {}
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
		_rb_tree_iterator() ___NOEXCEPT__ : __node() {}
		explicit _rb_tree_iterator(_base_ptr __x) ___NOEXCEPT__ : __node(__x)
		{
		} // Set base ptr with __X

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

		// friend bool operator==(const _self &__x, const _self &__y) ___NOEXCEPT__
		// {
		// 	return __x.__node == __y.__node;
		// }

		// friend bool operator!=(const _self &__x, const _self &__y) ___NOEXCEPT__
		// {
		// 	return __x.__node != __y.__node;
		// }
	}; // End of _rb_tree_iterator

	template <typename _Tp>
	bool operator==(const _rb_tree_iterator<_Tp> &__x, const _rb_tree_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return __x.__node == __y.__node;
	}

	template <typename _Tp>
	bool operator!=(const _rb_tree_iterator<_Tp> &__x, const _rb_tree_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return __x.__node != __y.__node;
	}

	template <typename _Tp>
	struct _rb_tree_const_iterator
	{
		typedef _Tp value_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;

		typedef _rb_tree_iterator<_Tp> iterator;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _rb_tree_const_iterator<_Tp> _self_const;
		typedef _rb_tree_node_base::_const_base_ptr _base_ptr;
		typedef const _rb_tree_node<_Tp> *_link_type;

		_base_ptr __node;

		// *--*--*--*--*--*--*--*--*--*--*
		// Functor constructor
		_rb_tree_const_iterator() ___NOEXCEPT__ : __node() {}
		explicit _rb_tree_const_iterator(_base_ptr __x) ___NOEXCEPT__ : __node(__x)
		{
		} // Set base ptr with __X
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

		_self_const &operator++() ___NOEXCEPT__
		{
			__node = _rb_tree_increment(__node);
			return *this;
		}

		_self_const operator++(int) ___NOEXCEPT__
		{
			_self_const __tmp = *this;
			__node = _rb_tree_increment(__node);
			return __tmp;
		}

		_self_const &operator--() ___NOEXCEPT__
		{
			__node = _rb_tree_decrement(__node);
			return *this;
		}

		_self_const operator--(int) ___NOEXCEPT__
		{
			_self_const __tmp = *this;
			__node = _rb_tree_decrement(__node);
			return __tmp;
		}

		// friend bool operator==(const _self_const &__x,
		// 					   const _self_const &__y) ___NOEXCEPT__
		// {
		// 	return __x.__node == __y.__node;
		// }

		// friend bool operator!=(const _self_const &__x,
		// 					   const _self_const &__y) ___NOEXCEPT__
		// {
		// 	return __x.__node != __y.__node;
		// }
	}; // End of _rb_tree_const_iterator

	template <typename _Tp>
	bool operator==(const _rb_tree_const_iterator<_Tp> &__x, const _rb_tree_const_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return __x.__node == __y.__node;
	}

	template <typename _Tp>
	bool operator==(const _rb_tree_const_iterator<_Tp> &__x, const _rb_tree_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return __x.__node == __y.__node;
	}

	template <typename _Tp>
	bool operator==(const _rb_tree_iterator<_Tp> &__x, const _rb_tree_const_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return __x.__node == __y.__node;
	}

	template <typename _Tp>
	bool operator!=(const _rb_tree_const_iterator<_Tp> &__x, const _rb_tree_const_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return !(__x.__node == __y.__node);
	}

	template <typename _Tp>
	bool operator!=(const _rb_tree_const_iterator<_Tp> &__x, const _rb_tree_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return !(__x.__node == __y.__node);
	}

	template <typename _Tp>
	bool operator!=(const _rb_tree_iterator<_Tp> &__x, const _rb_tree_const_iterator<_Tp> &__y) ___NOEXCEPT__
	{
		return !(__x.__node == __y.__node);
	}

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// Red - Black tree
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc = std::allocator<_Value> >
	class _rb_tree
	{
		// allocator<_Value> other;
		typedef typename _Alloc::template rebind<_rb_tree_node<_Value> >::other
			_node_allocator;

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

		// iterator
		typedef _rb_tree_iterator<value_type> iterator;
		typedef _rb_tree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] Structure
	protected:
		template <typename _Key_compare>
		struct _rb_tree_impl : public _node_allocator,
							   public _rb_tree_key_compare<_Key_compare>,
							   public _rb_tree_header
		{
			typedef _rb_tree_key_compare<_Key_compare> _base_key_compare;

			// Functor constructor
			_rb_tree_impl() ___NOEXCEPT__ : _node_allocator() {}

			_rb_tree_impl(const _rb_tree_impl &__x)
				: _node_allocator(__x),
				  _base_key_compare(__x.__key_compare),
				  _rb_tree_header() {}

			_rb_tree_impl(const _Key_compare &__comp, const _node_allocator &__a)
				: _node_allocator(__a), _base_key_compare(__comp) {}
		};

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] Member variable
	protected:
		_rb_tree_impl<_Compare> __impl; // node allocator?

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Public ] Function implementation
	public:
		_node_allocator &__get_node_allocator() ___NOEXCEPT__ { return this->__impl; }

		const _node_allocator &__get_node_allocator() const ___NOEXCEPT__
		{
			return this->__impl;
		}

		allocator_type get_allocator() const ___NOEXCEPT__
		{
			return allocator_type(__get_node_allocator());
		}

		ft::pair<_base_ptr, _base_ptr> __get_insert_hint_unique_pos(
			const_iterator __pos, const key_type &__k);

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Protected ] Function implementation
	protected:
		_link_type __allocate_node()
		{
			return this->__get_node_allocator().allocate(1);
		}

		void __deallocate_node(_link_type __p) ___NOEXCEPT__
		{
			this->__get_node_allocator().deallocate(__p, 1);
		}

		void __construct_node(_link_type __node,
							  const value_type &__x) // rb tree node, value
		{
			this->get_allocator().construct(__node->__valptr(), __x);
		}

		_link_type __create_node(const value_type &__x)
		{
			_link_type __tmp = __allocate_node();
			__construct_node(__tmp, __x);
			return __tmp;
		}

		void __destroy_node(_link_type __p) ___NOEXCEPT__
		{
			get_allocator().destroy(__p->__valptr());
		}

		void __drop_node(_link_type __p) ___NOEXCEPT__ // delete node
		{
			__destroy_node(__p);
			__deallocate_node(__p);
		}

		_link_type __clone_node(_link_type __x)
		{
			// _link_type __tmp = __node_gen(*__x->__valptr()); // Fix needed
			_link_type __tmp = this->__create_node(*__x->__valptr());
			__tmp->__color = __x->__color;
			__tmp->__left = 0;
			__tmp->__right = 0;
			return __tmp;
		}

		// RETURN SPECIFIC NODE
		_base_ptr &__root() ___NOEXCEPT__ { return this->__impl.__header.__parent; }

		_const_base_ptr __root() const ___NOEXCEPT__
		{
			return this->__impl.__header.__parent;
		}

		_base_ptr &__leftmost() ___NOEXCEPT__ { return this->__impl.__header.__left; }

		_const_base_ptr __leftmost() const ___NOEXCEPT__
		{
			return this->__impl.__header.__left;
		}

		_base_ptr &__rightmost() ___NOEXCEPT__
		{
			return this->__impl.__header.__right;
		}

		_const_base_ptr __rightmost() const ___NOEXCEPT__
		{
			return this->__impl.__header.__right;
		}

		_link_type __mbegin() const ___NOEXCEPT__
		{
			return static_cast<_link_type>(this->__impl.__header.__parent);
		}

		_link_type __begin() ___NOEXCEPT__ { return __mbegin(); }

		_const_link_type __begin() const ___NOEXCEPT__
		{
			return static_cast<_const_link_type>(this->__impl.__header.__parent);
		}

		_base_ptr __end() ___NOEXCEPT__ { return &this->__impl.__header; }

		_const_base_ptr __end() const ___NOEXCEPT__ { return &this->__impl.__header; }

		// RETURN KEY
		static const _Key &__key(_const_link_type __x)
		{
			return _KeyOfValue()(*__x->__valptr());
		}

		static const _Key &__key(_const_base_ptr __x)
		{
			return __key(static_cast<_const_link_type>(__x));
		}

		// RETURN NODE
		static _link_type __left(_base_ptr __x) ___NOEXCEPT__
		{
			return static_cast<_link_type>(__x->__left);
		}

		static _const_link_type __left(_const_base_ptr __x) ___NOEXCEPT__
		{
			return static_cast<_const_link_type>(__x->__left);
		}

		static _link_type __right(_base_ptr __x) ___NOEXCEPT__
		{
			return static_cast<_link_type>(__x->__right);
		}

		static _const_link_type __right(_const_base_ptr __x) ___NOEXCEPT__
		{
			return static_cast<_const_link_type>(__x->__right);
		}

		// RETURN MAX or MIN NODE
		static _base_ptr __minimum(_base_ptr __x) ___NOEXCEPT__
		{
			return _rb_tree_node_base::_s_minimum(__x);
		}

		static _const_base_ptr __minimum(_const_base_ptr __x) ___NOEXCEPT__
		{
			return _rb_tree_node_base::_s_minimum(__x);
		}

		static _base_ptr __maximum(_base_ptr __x) ___NOEXCEPT__
		{
			return _rb_tree_node_base::_s_maximum(__x);
		}

		static _const_base_ptr __maximum(_const_base_ptr __x) ___NOEXCEPT__
		{
			return _rb_tree_node_base::_s_maximum(__x);
		}

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Public ] Function prototype
	public:
		ft::pair<_base_ptr, _base_ptr> __get_insert_unique_pos(const key_type &__k);

		// *--*--*--*--*--*--*--*--*--*--*
		// [ Private ] Function implementation
	private:
		// template <typename _NodeGen>
		iterator __insert_(_base_ptr __x, _base_ptr __y, const value_type &__v);
		// template <bool _MoveValues, typename _NodeGen>
		_link_type __copy(_link_type __x, _base_ptr __y);
		// template <bool _MoveValues, typename _NodeGen>
		_link_type __copy(const _rb_tree &__x)
		{
			_link_type __root = __copy(const_cast<_link_type>(__x.__begin()), __end());
			__leftmost() = __minimum(__root);
			__rightmost() = __maximum(__root);
			__impl.__node_count = __x.__impl.__node_count;
			return __root;
		}

		void __erase(_link_type __x);
		iterator __lower_bound(_link_type __x, _base_ptr __y, const _Key &__k);
		const_iterator __lower_bound(_const_link_type __x, _const_base_ptr __y,
									 const _Key &__k) const;
		iterator __upper_bound(_link_type __x, _base_ptr __y, const _Key &__k);
		const_iterator __upper_bound(_const_link_type __x, _const_base_ptr __y,
									 const _Key &__k) const;

		void __erase_aux(const_iterator __position);
		void __erase_aux(const_iterator __first, const_iterator __last);

	public:
		_rb_tree() {}

		_rb_tree(const _Compare &__comp, const allocator_type &__a = allocator_type())
			: __impl(__comp, _node_allocator(__a)) {}

		_rb_tree(const _rb_tree &__x) : __impl(__x.__impl)
		{
			if (__x.__root() != 0)
				__root() = __copy(__x);
		}

		~_rb_tree() ___NOEXCEPT__ { __erase(__begin()); }

		_rb_tree &operator=(const _rb_tree &__x);

		// Accessors
		_Compare key_comp() const { return __impl.__key_compare; }

		iterator begin() ___NOEXCEPT__
		{
			return iterator(this->__impl.__header.__left);
		}

		const_iterator begin() const ___NOEXCEPT__
		{
			return const_iterator(this->__impl.__header.__left);
		}

		iterator end() ___NOEXCEPT__ { return iterator(&this->__impl.__header); }

		const_iterator end() const ___NOEXCEPT__
		{
			return const_iterator(&this->__impl.__header);
		}

		reverse_iterator rbegin() ___NOEXCEPT__ { return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const ___NOEXCEPT__
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() ___NOEXCEPT__ { return reverse_iterator(begin()); }

		const_reverse_iterator rend() const ___NOEXCEPT__
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const ___NOEXCEPT__ { return __impl.__node_count == 0; }

		size_type size() const ___NOEXCEPT__ { return __impl.__node_count; }

		size_type max_size() const ___NOEXCEPT__
		{
			return __get_node_allocator().max_size();
			// return static_cast<size_type>(std::min(
			// 	__get_node_allocator().max_size(),
			// 	static_cast<unsigned long>(std::numeric_limits<difference_type>::max())));
		}

		void swap(_rb_tree &__t) ___NOEXCEPT__;

		// *==*==*==*==*==*==*==*==*==*==*
		// Insert
		iterator __insert_unique_hint_pos(const_iterator __pos,
										  const value_type &__x);

		ft::pair<iterator, bool> __insert_unique(const value_type &__x);

		template <typename _InputIterator>
		void __insert_range_unique(_InputIterator __first, _InputIterator __last)
		{
			for (; __first != __last; ++__first)
				__insert_unique_hint_pos(end(), *__first);
		}

		void erase(iterator __position) { __erase_aux(__position); }

		void erase(const_iterator __position) { __erase_aux(__position); }

		size_type erase(const _Key &__x);

		void erase(iterator __first, iterator __last)
		{
			__erase_aux(__first, __last);
		}

		void erase(const_iterator __first, const_iterator __last)
		{
			__erase_aux(__first, __last);
		}

		void clear() ___NOEXCEPT__
		{
			__erase(__begin());
			__impl.__reset();
		}

		iterator find(const key_type &__k);
		const_iterator find(const key_type &__k) const;
		size_type count(const key_type &__k) const;
		iterator lower_bound(const key_type &__k)
		{
			return __lower_bound(__begin(), __end(), __k);
		}
		const_iterator lower_bound(const key_type &__k) const
		{
			return __lower_bound(__begin(), __end(), __k);
		}
		iterator upper_bound(const key_type &__k)
		{
			return __upper_bound(__begin(), __end(), __k);
		}
		const_iterator upper_bound(const key_type &__k) const
		{
			return __upper_bound(__begin(), __end(), __k);
		}

		pair<iterator, iterator> equal_range(const key_type &__k);

		pair<const_iterator, const_iterator> equal_range(const key_type &__k) const;

		// friend bool operator==(const _rb_tree &__x, const _rb_tree &__y)
		// {
		// 	return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(),
		// __y.begin());
		// }

		// friend bool operator<(const _rb_tree &__x, const _rb_tree &__y)
		// {
		// 	return ft::lexicographical_compare(__x.begin(), __x.end(),
		// 									   __y.begin(),
		// __y.end());
		// }

	}; // Finally red - black 'class' is entrance

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void swap(_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> &__x,
			  _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		__x.swap(__y);
	}

	// *--*--*--*--*--*--*--*--*--*--*
	// Member function implementation

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(
		const key_type &__k)
	{
		iterator __j = __lower_bound(__begin(), __end(), __k);
		return (__j == end() || __impl.__key_compare(__k, __key(__j.__node))) ? end()
																			  : __j;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(
		const key_type &__k) const
	{
		const_iterator __j = __lower_bound(__begin(), __end(), __k);
		return (__j == end() || __impl.__key_compare(__k, __key(__j.__node))) ? end()
																			  : __j;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::count(
		const key_type &__k) const
	{
		ft::pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = ft::distance(__p.first, __p.second);
		return __n;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>
		&_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::operator=(
			const _rb_tree &__x)
	{
		if (this != &__x)
		{
			// this->clear(); // How about this?
			__impl.__reset();
			__impl.__key_compare = __x.__impl.__key_compare;
			if (__x.__root() != 0)
				__root() = __copy(__x);
		}
		return *this;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__erase_aux(
		const_iterator __position)
	{
		_link_type __y = static_cast<_link_type>(_rb_tree_rebalance_for_erase(
			const_cast<_base_ptr>(__position.__node), this->__impl.__header));
		__drop_node(__y);
		--__impl.__node_count;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__erase_aux(
		const_iterator __first, const_iterator __last)
	{
		if (__first == begin() && __last == end())
		{
			clear();
		}
		else
		{
			while (__first != __last)
				__erase_aux(__first++);
		}
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__insert_(
		_base_ptr __x, _base_ptr __p, const _Value &__v)
	{
		bool __insert_left = (__x != 0 || __p == __end() ||
							  __impl.__key_compare(_KeyOfValue()(__v), __key(__p)));
		_link_type __z = this->__create_node(__v);
		_rb_tree_insert_and_rebalance(__insert_left, __z, __p, this->__impl.__header);
		++__impl.__node_count;
		return iterator(__z);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_link_type
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__copy(_link_type __x,
																  _base_ptr __p)
	{
		_link_type __top = __clone_node(__x); // new node with __x
		__top->__parent = __p;

		if (__x->__right)
			__top->__right = __copy(__right(__x), __top);
		__p = __top;
		__x = __left(__x);

		while (__x != 0)
		{
			_link_type __y = __clone_node(__x);
			__p->__left = __y;
			__y->__parent = __p;
			if (__x->__right)
				__y->__right = __copy(__right(__x), __y);
			__p = __y;
			__x = __left(__x);
		}
		return __top;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__erase(
		_link_type __x)
	{
		while (__x != 0)
		{
			__erase(__right(__x));
			_link_type __y = __left(__x);
			__drop_node(__x);
			__x = __y;
		}
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__lower_bound(
		_link_type __x, _base_ptr __y, const _Key &__k)
	{
		while (__x != 0)
		{
			if (!__impl.__key_compare(__key(__x), __k))
			{
				__y = __x;
				__x = __left(__x);
			}
			else
				__x = __right(__x);
		}
		return iterator(__y);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__lower_bound(
		_const_link_type __x, _const_base_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
		{
			if (!__impl.__key_compare(__key(__x), __k))
			{
				__y = __x;
				__x = __left(__x);
			}
			else
				__x = __right(__x);
		}
		return const_iterator(__y);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__upper_bound(
		_link_type __x, _base_ptr __y, const _Key &__k)
	{
		while (__x != 0)
			if (__impl.__key_compare(__k, __key(__x)))
				__y = __x, __x = __left(__x);
			else
				__x = __right(__x);
		return iterator(__y);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__upper_bound(
		_const_link_type __x, _const_base_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
			if (__impl.__key_compare(__k, __key(__x)))
				__y = __x, __x = __left(__x);
			else
				__x = __right(__x);
		return const_iterator(__y);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	ft::pair<
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator,
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::equal_range(
		const key_type &__k)
	{
		_link_type __x = __begin();
		_base_ptr __y = __end();
		while (__x != 0)
		{
			if (__impl.__key_compare(__key(__x), __k))
				__x = __right(__x);
			else if (__impl.__key_compare(__k, __key(__x)))
			{
				__y = __x;
				__x = __left(__x);
			}
			else
			{
				_link_type __xu(__x);
				_base_ptr __yu(__y);
				__y = __x;
				__x = __left(__x);
				__xu = __right(__xu);
				return ft::pair<iterator, iterator>(__lower_bound(__x, __y, __k),
													__upper_bound(__xu, __yu, __k));
			}
		}
		return ft::pair<iterator, iterator>(iterator(__y), iterator(__y));
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	ft::pair<typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare,
							   _Alloc>::const_iterator,
			 typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare,
							   _Alloc>::const_iterator>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::equal_range(
		const key_type &__k) const
	{
		_const_link_type __x = __begin();
		_const_base_ptr __y = __end();
		while (__x != 0)
		{
			if (__impl.__key_compare(__key(__x), __k))
				__x = __right(__x);
			else if (__impl.__key_compare(__k, __key(__x)))
				__y = __x, __x = __left(__x);
			else
			{
				_const_link_type __xu(__x);
				_const_base_ptr __yu(__y);
				__y = __x, __x = __left(__x);
				__xu = __right(__xu);
				return ft::pair<const_iterator, const_iterator>(
					__lower_bound(__x, __y, __k), __upper_bound(__xu, __yu, __k));
			}
		}
		return ft::pair<const_iterator, const_iterator>(const_iterator(__y),
														const_iterator(__y));
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::swap(_rb_tree &__t)
		___NOEXCEPT__
	{
		if (__root() == 0)
		{
			if (__t.__root() != 0)
				__impl.__move_data(__t.__impl);
		}
		else if (__t.__root() == 0)
			__t.__impl.__move_data(__impl);
		else
		{
			ft::swap(__root(), __t.__root());
			ft::swap(__leftmost(), __t.__leftmost());
			ft::swap(__rightmost(), __t.__rightmost());

			__root()->__parent = __end();
			__t.__root()->__parent = __t.__end();
			ft::swap(this->__impl.__node_count, __t.__impl.__node_count);
		}
		ft::swap(this->__impl.__key_compare, __t.__impl.__key_compare);
		ft::swap(this->__get_node_allocator(), __t.__get_node_allocator());
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	ft::pair<
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_base_ptr,
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_base_ptr>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__get_insert_unique_pos(
		const key_type &__k)
	{
		// __k = insert node's key
		// pair<first, last>
		// first : if not null, insert left. Or insert right.
		// second : if not null, parent of node will be inserted
		//			if null, node will not be inserted.
		// pair typedef
		typedef pair<_base_ptr, _base_ptr> _Res;
		_link_type __x = __begin();
		_base_ptr __y = __end();

		bool __comp = true;
		while (__x != 0)
		{
			__y = __x; // y might be leafnode
			__comp = __impl.__key_compare(
				__k, __key(__x));					   // new node's key is smaller than __x's key
			__x = __comp ? __left(__x) : __right(__x); // if __k is smaller than __x,
													   // __x is going to left node
		}
		iterator __j = iterator(__y);
		if (__comp) // k < key of x
		{
			if (__j == begin())		   // root
				return _Res(__x, __y); // the first node will be inserted at left
			else
				--__j; // decrement
		}
		if (__impl.__key_compare(__key(__j.__node),
								 __k)) // if j's key is smaller than __k
			return _Res(__x, __y);	   // new node will be inserted at __y's left
		return _Res(__j.__node, 0);	   // node will not be inserted, equivalent key..
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	ft::pair<
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_base_ptr,
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_base_ptr>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare,
			 _Alloc>::__get_insert_hint_unique_pos(const_iterator __position,
												   const key_type &__k)
	{
		// _M_get_insert_hint_unique_pos(const_iterator __position, const key_type
		// &__k)
		// __k = insert node's key
		// pair<first, last>
		// first : if not null, insert left. Or insert right.
		// second : if not null, parent of node will be inserted
		//			if null, node will not be inserted.
		iterator __pos = __position.__const_cast(); // Make const
		typedef pair<_base_ptr, _base_ptr> _Res;	// pair typedef

		if (__pos.__node == __end()) // if position's node is end node
		{
			// if tree is not empty and new node's key is bigger than rightmost
			// return 0, rightmost
			if (size() > 0 && __impl.__key_compare(__key(__rightmost()), __k))
				return _Res(0, __rightmost()); // insert right at rightmost's child
			else							   // tree is empty or new node's key is smaller than rightmost, insert
											   // node root location
				return __get_insert_unique_pos(__k);
		}
		else if (__impl.__key_compare(
					 __k,
					 __key(__pos.__node))) // __k is smaller than position's node
		{
			iterator __before = __pos;
			if (__pos.__node == __leftmost()) //
				return _Res(__leftmost(),
							__leftmost()); // will be inserted leftmost's left position
			else if (__impl.__key_compare(__key((--__before).__node), __k))
			{
				if (__right(__before.__node) == 0)			 // __before's right is nil
					return _Res(0, __before.__node);		 //
				else										 // __before's right is not nil.
					return _Res(__pos.__node, __pos.__node); // will be inserted
			}
			else
				return __get_insert_unique_pos(__k);
		}
		else if (__impl.__key_compare(__key(__pos.__node),
									  __k)) // k is bigger than pos's node
		{
			iterator __after = __pos;
			if (__pos.__node == __rightmost())
				return _Res(0, __rightmost());
			else if (__impl.__key_compare(__k, __key((++__after).__node)))
			{
				if (__right(__pos.__node) == 0)
					return _Res(0, __pos.__node);
				else
					return _Res(__after.__node, __after.__node);
			}
			else
				return __get_insert_unique_pos(__k);
		}
		else
			return _Res(__pos.__node, 0); // Equivalent key
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__insert_unique_hint_pos(
		const_iterator __pos, const value_type &__x)
	{
		// pos: end, value_type: *first
		ft::pair<_base_ptr, _base_ptr> __res =
			__get_insert_hint_unique_pos(__pos, _KeyOfValue()(__x));

		if (__res.second) // if pair's second is null, the node will not be inserted.
			return __insert_(__res.first, __res.second, __x);
		return iterator(__res.first);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	ft::pair<
		typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator,
		bool>
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__insert_unique(
		const value_type &__x)
	{
		typedef ft::pair<iterator, bool> _Res;
		ft::pair<_base_ptr, _base_ptr> __res =
			__get_insert_unique_pos(_KeyOfValue()(__x));
		// first : if not null, insert left. Or insert right.
		// second : if not null, parent of node will be inserted
		//			if null, node will not be inserted.
		if (__res.second)
		{
			return _Res(__insert_(__res.first, __res.second, __x), true);
		}
		return _Res(iterator(__res.first), false);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
	_rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(const _Key &__x)
	{
		ft::pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		__erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
	// EXAMPLE
	// *==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*
} // namespace ft

#endif
