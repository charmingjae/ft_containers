/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:09:12 by mcha              #+#    #+#             */
/*   Updated: 2022/08/01 18:16:19 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#define _NOEXCEPT throw()

/* include */
#include <iterator>  // iterator
#include <limits>    // limits
#include <memory>    // allocator
#include <stdexcept> // except

/* namespace : ft */
namespace ft {
/* class template : vector_base */
/*
 *	class _Tp : type of the elements
 *	class _Allocator : An allocator that is used to acquire/release memory
 *	and to construct/destroy the elements in that memory.
 */
template <typename _Tp, typename _Allocator = std::allocator<_Tp>()>
class __vector_base {
  public: // LLVM vector
    typedef _Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    //   protected: // LLVM vector
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

    void clear(void) _NOEXCEPT { __destruct_at_end(__begin_); }

    void __destruct_at_end(pointer __new_last) _NOEXCEPT;

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
};

/* Implement */
// -> Constructor
template <typename _Tp, typename _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base() _NOEXCEPT
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr),
      __a_(allocator_type()) {}

template <typename _Tp, typename _Allocator>
__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a)
    : __begin_(nullptr), __end_(nullptr), __end_cap_(__a), __a_(__a) {}

// -> Destructor
template <typename _Tp, typename _Allocator>
__vector_base<_Tp, _Allocator>::~__vector_base() {
    if (__begin_ != nullptr) {
        clear();                               // 1. destroy the object
        __a_.deallocate(__begin_, capacity()); // 2. deallocate allocated memory
    }
}

// -> __destruct_at_end
template <typename _Tp, typename _Allocator>
void __vector_base<_Tp, _Allocator>::__destruct_at_end(
    pointer __new_last) _NOEXCEPT {
    pointer __soon_to_be_end = __end_;
    while (__new_last != __soon_to_be_end) {
        __a_.destroy(--__soon_to_be_end);
    }
    __end_ = __new_last;
}

/* class template : vector */
/*
 *	class T : type of the elements
 *	class Allocator : An allocator that is used to acquire/release memory
 *	and to construct/destroy the elements in that memory.
 *	Inherit vector_base template
 */
template <typename _Tp, typename _Allocator = std::allocator<_Tp>()>
class vector : private __vector_base<_Tp, _Allocator> {
  private:
    typedef __vector_base<_Tp, _Allocator> __base;
    typedef allocator<_Tp> __default_allocator_type;
    void __vallocate(size_type __n);

  public:
    typedef _Tp value_type;
    typedef _Allocator allocator_type;
    typedef typename __base::reference reference;
    typedef typename __base::const_reference const_reference;
    typedef typename __base::size_type size_type;
    typedef typename __base::difference_type difference_type;
    typedef typename __base::pointer pointer;
    typedef typename __base::const_pointer const_pointer;
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // typedef __wrap_iter<pointer>				iterator;
    // typedef __wrap_iter<pointer>				const_iterator;
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////

    // Constructor & Destructor
    vector() _NOEXCEPT;
    explicit vector(const allocator_type &__a) _NOEXCEPT : __base(__a);
    explicit vector(size_type __n);
    vector(size_type __n, const value_type &__x);
    vector(size_type __n, const value_type &__x, const allocator_type &__a);
    ~vector();

    // function
    void push_back(const_reference __x);
    void pop_back();
    size_type max_size() const _NOEXCEPT;
    void __construct_at_end(size_typq __n);

    // throw
    void __throw_length_error(const char *__msg) { throw length_error(__msg); }
};

// Implementation

// -> Allocate
////////////////////////////////////////////////////////////////
template <typename _Tp, typename _Allocator>
void vector<_Tp, _Allocator>::__vallocate(size_type __n)
    : __a_(std::allocator<_Tp>()) {
    // 1. check is n bigger than max_size
    if (__n > max_size())
        this->__throw_length_error("vector : max size exception");
    // 2. Set begin, end
    this->__begin_ = this->__end_ = this->__a_.allocate(__n);
    // 3. Set end capacity
    this->__end_cap_ = this->__begin_ + __n;
}
////////////////////////////////////////////////////////////////

// -> Constructor : create N size vector
template <typename _Tp, typename _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n) {
    if (__n > 0) {               // if size is bigger than 0
        __vallocate(__n);        // 1. allocate
        __construct_at_end(__n); // 2. construct
    }
}

// -> max_size()
template <typename _Tp, typename _Allocator>
typename vector<_Tp, _Allocator>::size_type
vector<_Tp, _Allocator>::max_size() const _NOEXCEPT {
    return static_cast<size_type>(std::min(
        this->__a_.max_size(), std::numeric_limits<difference_type>::max()));
}

} // namespace ft

#endif