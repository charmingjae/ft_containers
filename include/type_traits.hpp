/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:47:18 by mcha              #+#    #+#             */
/*   Updated: 2022/08/22 21:20:05 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

// --*-- Define in type_traits --*--
#define ___NOEXCEPT__ throw()

namespace ft
{
	// integral_constant
	template <typename _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp value = __v; // constexpr
		typedef _Tp value_type;
		typedef integral_constant type;
		operator value_type() const ___NOEXCEPT__ { return value; } // constexpr
	};

	// true_type , false_type
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// enable_if
	template <bool Cond, typename T = void>
	struct enable_if
	{
	};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// is_same
	// -> Primary template
	template <typename _Tp, typename _Up>
	struct is_same : public false_type
	{
	};

	// -> Specialization template
	template <typename _Tp>
	struct is_same<_Tp, _Tp> : public true_type
	{
	};

	// remove_const
	template <typename _Tp>
	struct remove_const
	{
		typedef _Tp type;
	};
	template <typename _Tp>
	struct remove_const<const _Tp>
	{
		typedef _Tp type;
	};

	// remove_volatile
	template <typename _Tp>
	struct remove_volatile
	{
		typedef _Tp type;
	};
	template <typename _Tp>
	struct remove_volatile<volatile _Tp>
	{
		typedef _Tp type;
	};

	// remove_cv
	template <typename _Tp>
	struct remove_cv
	{
		typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;
	};

	// __void_t
	template <typename>
	struct __void_t
	{
		typedef void type;
	};

	// is_integral
	template <class _Tp>
	struct __libcpp_is_integral : public false_type
	{
	};
	template <>
	struct __libcpp_is_integral<bool> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<char> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<signed char> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<unsigned char> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<wchar_t> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<short> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<unsigned short> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<int> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<unsigned int> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<long> : public true_type
	{
	};
	template <>
	struct __libcpp_is_integral<unsigned long> : public true_type
	{
	};

	template <typename _Tp>
	struct is_integral
		: public __libcpp_is_integral<typename remove_cv<_Tp>::type>
	{
	};
} // namespace ft

#endif