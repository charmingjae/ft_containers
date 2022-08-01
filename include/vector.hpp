/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:09:12 by mcha              #+#    #+#             */
/*   Updated: 2022/08/01 14:56:20 by mcha             ###   ########.fr       */
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
    typedef typename allocator_type::size_type size_type;

  protected: // LLVM vector
    typedef _Tp value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef pointer iterator;
    typedef const_pointer const_iterator;

    // pointer
    pointer __begin_;
    pointer __end_;     // size
    pointer __end_cap_; // capacity -> gcc vector
    allocator_type __a_;

    // Constructor & destructor
    __vector_base() _NOEXCEPT;
    __vector_base(const allocator_type &__a);
    ~__vector_base();

    // Allocator
    // allocator_type &__alloc() _NOEXCEPT {}

    // function
    size_type capacity(void) const _NOEXCEPT {
        return static_cast<size_type>(__end_cap_ - __begin_);
    };

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    void __destruct_at_end(pointer __new_last) _NOEXCEPT;

    void clear(void) _NOEXCEPT { __destruct_at_end(__begin_); }

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
};

/* Implement */
// -> Constructor
template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr),
      __a_(std::allocator<_Tp>) {}

// -> Constructor
template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a)
    : __begin_(nullptr), __end_(nullptr), __end_cap_(__a), __a_(__a) {}

// -> Destructor
template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::~__vector_base() {
    if (__begin_ != nullptr) {
        // clear();
        __alloc_traits::deallocate(__begin_, __capacity());
    }
}

// -> __destruct_at_end

template <class _Tp, class _Allocator>
void __vector_base<_Tp, _Allocator>::__destruct_at_end(
    pointer __new_last) _NOEXCEPT {
    pointer __soon_to_be_end = __end_;
    while (__new_last != __soon_to_be_end) {
        // destroy
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