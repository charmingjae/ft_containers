/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:40:29 by mcha              #+#    #+#             */
/*   Updated: 2022/08/22 21:13:53 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

// --*-- Define --*--
#define ___NOEXCEPT__ throw()

// --*-- Include --*--
#include <cstddef>

#include "type_traits.hpp"

namespace ft
{
	// --*-- Iterator traits struct prototype --*--
	template <typename _Iter>
	struct iterator_traits;

	// --*-- Iterator tag --*--

#ifdef _LIBCPP_ITERATOR
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;
#else
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};
#endif

	// --*--*--*--*--*--*--*--
	// 		Base iterator
	// --*--*--*--*--*--*--*--
	template <typename Category,			 // iterator::iterator_category
			  typename T,					 // iterator::value_type
			  typename Distance = ptrdiff_t, // iterator::difference_type
			  typename Pointer = T *,		 // iterator::pointer
			  typename Reference = T &		 // iterator::reference
			  >
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	// --*-- Check _Tp has iterator typedef --*--
	template <typename _Tp>
	struct __has_iterator_typedefs
	{
	private:
		struct __two
		{
			char __lx;
			char __lxx;
		};
		template <typename _Up>
		static __two __test(...);
		template <typename _Up>
		static char __test(
			typename ft::__void_t<typename _Up::iterator_category>::type * = 0,
			typename ft::__void_t<typename _Up::difference_type>::type * = 0,
			typename ft::__void_t<typename _Up::value_type>::type * = 0,
			typename ft::__void_t<typename _Up::reference>::type * = 0,
			typename ft::__void_t<typename _Up::pointer>::type * = 0);

	public:
		static const bool value = sizeof(__test<_Tp>(0, 0, 0, 0, 0)) == 1;
	};

	// --*-- Is _Tp has iterator category --*--
	template <typename _Tp>
	struct __has_iterator_category
	{
	private:
		struct __two
		{
			char __lx;
			char __lxx;
		};
		template <typename _Up>
		static __two __test(...);
		template <typename _Up>
		static char __test(typename _Up::iterator_category * = 0);

	public:
		static const bool value = sizeof(__test<_Tp>(0)) == 1;
	};

	// --*-- Iterator traits implementation --*--
	// traits -> primary template
	template <typename _Iter, bool>
	struct __iterator_traits_impl
	{
	};

	// --*-- Iterator traits implementation --*--
	// traits -> specialization template
	template <typename _Iter>
	struct __iterator_traits_impl<_Iter, true>
	{
		typedef typename _Iter::difference_type difference_type;
		typedef typename _Iter::value_type value_type;
		typedef typename _Iter::pointer pointer;
		typedef typename _Iter::reference reference;
		typedef typename _Iter::iterator_category iterator_category;
	};

	// --*-- iterator traits type traits --*--
	// -> Primary template
	template <typename _Iter, bool>
	struct __iterator_traits
	{
	};

	// --*-- iterator traits type traits --*--
	// --> Specialization template
	template <typename _Iter>
	struct __iterator_traits<_Iter, true>
		: __iterator_traits_impl<_Iter,
								 is_same<typename _Iter::iterator_category,
										 input_iterator_tag>::value ||
									 is_same<typename _Iter::iterator_category,
											 output_iterator_tag>::value ||
									 is_same<typename _Iter::iterator_category,
											 forward_iterator_tag>::value ||
									 is_same<typename _Iter::iterator_category,
											 bidirectional_iterator_tag>::value ||
									 is_same<typename _Iter::iterator_category,
											 random_access_iterator_tag>::value>
	{
	};

	// --*-- iterator_traits --*--
	template <typename _Iter>
	struct iterator_traits
		: __iterator_traits<_Iter, __has_iterator_typedefs<_Iter>::value>
	{
	};

	template <typename _Tp>
	struct iterator_traits<_Tp *>
	{
		typedef ptrdiff_t difference_type;
		typedef typename remove_cv<_Tp>::type value_type; // type_traits
		typedef _Tp *pointer;
		typedef _Tp &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename _Tp>
	struct iterator_traits<const _Tp *>
	{
		typedef ptrdiff_t difference_type;
		typedef typename remove_cv<_Tp>::type value_type; // type_traits
		typedef const _Tp *pointer;
		typedef const _Tp &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	// --*-- DEPRECATED 22. 08. 08. --*--
	// // --*-- has iterator category convertible to --*--
	// template <typename _Tp, typename _Up, bool =
	// __has_iterator_category<iterator_traits<_Tp> >::value> struct
	// __has_iterator_category_convertible_to : public integral_constant<bool,
	// is_same<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
	// {
	// };

	// template <typename _Tp, typename _Up>
	// struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public
	// false_type
	// {
	// };

	// --*-- is iterator --*--

	// -> Primary template
	template <typename _Iter,
			  bool = __has_iterator_typedefs<iterator_traits<_Iter> >::value>
	struct __is_iterator
		: public integral_constant<
			  bool, __has_iterator_category<iterator_traits<_Iter> >::value>
	{
		typedef typename _Iter::iterator_category category;
	};

	// -> Specialization template with false type
	template <typename _Iter>
	struct __is_iterator<_Iter, false> : public false_type
	{
		typedef void category;
	};

	template <typename _Tp>
	struct __is_iterator<_Tp *, true> : public true_type
	{
		typedef typename iterator_traits<_Tp *>::iterator_category category;
		// typedef random_access_iterator_tag iterator_category;
	};

	// --*-- is ... iterator --*--
	template <typename _Iter>
	struct __is_input_iterator
		: public integral_constant<
			  bool, is_same<typename __is_iterator<_Iter>::category,
							input_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								forward_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								bidirectional_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								random_access_iterator_tag>::value>
	{
	};

	template <typename _Iter>
	struct __is_forward_iterator
		: public integral_constant<
			  bool, is_same<typename __is_iterator<_Iter>::category,
							forward_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								bidirectional_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								random_access_iterator_tag>::value>
	{
	};

	template <typename _Iter>
	struct __is_bidirectional_iterator
		: public integral_constant<
			  bool, is_same<typename __is_iterator<_Iter>::category,
							bidirectional_iterator_tag>::value ||
						is_same<typename __is_iterator<_Iter>::category,
								random_access_iterator_tag>::value>
	{
	};

	template <typename _Iter>
	struct __is_random_access_iterator
		: public integral_constant<bool,
								   is_same<typename __is_iterator<_Iter>::category,
										   random_access_iterator_tag>::value>
	{
	};

	template <typename _Iter>
	struct __is_output_iterator
		: public integral_constant<bool,
								   is_same<typename __is_iterator<_Iter>::category,
										   output_iterator_tag>::value>
	{
	};

	// --*-- Iterator operator --*--
	// --*-- advance --*--
	template <typename _InputIter>
	void __advance(_InputIter &__i,
				   typename iterator_traits<_InputIter>::difference_type __n,
				   input_iterator_tag)
	{
		for (; __n > 0; --__n)
			++__i;
	}

	template <typename _BiDirIter>
	void __advance(_BiDirIter &__i,
				   typename iterator_traits<_BiDirIter>::difference_type __n,
				   bidirectional_iterator_tag)
	{
		if (__n >= 0)
			for (; __n > 0; --__n)
				++__i;
		else
			for (; __n < 0; ++__n)
				--__i;
	}

	template <typename _RandIter>
	void __advance(_RandIter &__i,
				   typename iterator_traits<_RandIter>::difference_type __n,
				   random_access_iterator_tag)
	{
		__i += __n;
	}

	template <typename _InputIter>
	void advance(_InputIter &__i,
				 typename iterator_traits<_InputIter>::difference_type __n)
	{
		__advance(__i, __n,
				  typename iterator_traits<_InputIter>::iterator_category());
	}

	// --*-- distance --*--
	template <typename _InputIter>
	typename iterator_traits<_InputIter>::difference_type __distance(
		_InputIter __first, _InputIter __last, input_iterator_tag)
	{
		typename iterator_traits<_InputIter>::difference_type __r(0);
		for (; __first != __last; ++__first)
			++__r;
		return __r;
	}

	template <typename _RandIter>
	typename iterator_traits<_RandIter>::difference_type __distance(
		_RandIter __first, _RandIter __last, random_access_iterator_tag)
	{
		return __last - __first;
	}

	template <typename _InputIter>
	typename iterator_traits<_InputIter>::difference_type distance(
		_InputIter __first, _InputIter __last)
	{
		return ft::__distance(
			__first, __last,
			typename iterator_traits<_InputIter>::iterator_category());
	}

	// --*--*--*--*--*--*--*--
	// 	Reverse iterator
	// --*--*--*--*--*--*--*--
	template <typename _Iter>
	class reverse_iterator
		: public iterator<typename iterator_traits<_Iter>::iterator_category,
						  typename iterator_traits<_Iter>::value_type,
						  typename iterator_traits<_Iter>::difference_type,
						  typename iterator_traits<_Iter>::pointer,
						  typename iterator_traits<_Iter>::reference>
	{
	private:
		_Iter __t;

	protected:
		_Iter current;

	public:
		typedef _Iter iterator_type;
		typedef typename iterator_traits<_Iter>::difference_type difference_type;
		typedef typename iterator_traits<_Iter>::reference reference;
		typedef typename iterator_traits<_Iter>::pointer pointer;

		// --*-- Constructor --*--
		reverse_iterator() : __t(), current() {}
		explicit reverse_iterator(_Iter __x) : __t(__x), current(__x) {}
		template <typename _Up>
		reverse_iterator(const reverse_iterator<_Up> &__u)
			: __t(__u.base()), current(__u.base()) {}
		template <typename _Up>
		reverse_iterator &operator=(const reverse_iterator<_Up> &__u)
		{
			__t = current = __u.base();
			return *this;
		}
		_Iter base() const { return current; }
		reference operator*() const
		{
			_Iter __tmp = current;
			return *--__tmp;
		}
		pointer operator->() const { return &(operator*()); }
		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator __tmp(*this);
			--current;
			return __tmp;
		}
		reverse_iterator &operator--()
		{
			++current;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator __tmp(*this);
			++current;
			return __tmp;
		}
		reverse_iterator operator+(difference_type __n) const
		{
			return reverse_iterator(current - __n);
		}
		reverse_iterator &operator+=(difference_type __n)
		{
			current -= __n;
			return *this;
		}
		reverse_iterator operator-(difference_type __n) const
		{
			return reverse_iterator(current + __n);
		}
		reverse_iterator &operator-=(difference_type __n)
		{
			current += __n;
			return *this;
		}
		reference operator[](difference_type __n) const { return *(*this + __n); }
	};

	// --*-- Non member function (operator) --*--

	template <typename _Iter1, typename _Iter2>
	bool operator==(const reverse_iterator<_Iter1> &__x,
					const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() == __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator<(const reverse_iterator<_Iter1> &__x,
				   const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() > __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator!=(const reverse_iterator<_Iter1> &__x,
					const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() != __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator>(const reverse_iterator<_Iter1> &__x,
				   const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() < __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator>=(const reverse_iterator<_Iter1> &__x,
					const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() <= __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	bool operator<=(const reverse_iterator<_Iter1> &__x,
					const reverse_iterator<_Iter2> &__y)
	{
		return __x.base() >= __y.base();
	}

	template <typename _Iter1, typename _Iter2>
	typename reverse_iterator<_Iter1>::difference_type operator-(
		const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
	{
		return __y.base() - __x.base();
	}

	template <typename _Iter>
	reverse_iterator<_Iter> operator+(
		typename reverse_iterator<_Iter>::difference_type __n,
		const reverse_iterator<_Iter> &__x)
	{
		return reverse_iterator<_Iter>(__x.base() - __n);
	}

} // namespace ft

#endif