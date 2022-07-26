/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:09:12 by mcha              #+#    #+#             */
/*   Updated: 2022/07/26 20:33:46 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#define _NOEXCEPT throw()

/* include */
#include <memory> // allocator

/* namespace : ft */
namespace ft {
/* vector base */
template <class _Tp, class _Allocator> class __vector_base {
  public: // LLVM vector
    typedef _Allocator allocator_type;
    typedef allocator_traits<allocator_type> __alloc_traits;
    typedef typename __alloc_traits::size_type size_type;

  protected: // LLVM vector
    typedef _Tp value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef typename __alloc_traits::pointer pointer;
    typedef typename __alloc_traits::const_pointer const_pointer;
    typedef pointer iterator;
    typedef const_pointer const_iterator;

    // pointer
    pointer __begin_;
    pointer __end_;     // size
    pointer __end_cap_; // capacity -> gcc vector

    // Constructor & destructor
    __vector_base() _NOEXCEPT;
    __vector_base(const allocator_type &__a);
    ~__vector_base();
};

/* Implement */
template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr) {}

template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a)
    : __begin_(nullptr), __end_(nullptr), __end_cap_(__a) {}

template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::~__vector_base() {
    if (__begin_ != nullptr) {
        // clear();
        __alloc_traits::deallocate(__begin_, __capacity());
    }
}

/* class template : vector */
/*
 *	class T : type of the elements
 *	class Allocator : An allocator that is used to acquire/release memory
 *	and to construct/destroy the elements in that memory.
 */

} // namespace ft

#endif