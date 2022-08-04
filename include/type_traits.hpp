/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:47:18 by mcha              #+#    #+#             */
/*   Updated: 2022/08/04 18:10:52 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS
#define TYPE_TRAITS

namespace ft
{
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

	// integral constant
	template <typename T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, value> type;
		operator value_type() const { return value; } // constexpr -> const
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// is_same
	template <typename T, typename U>
	struct is_same : public false_type
	{
	};

	template <typename T>
	struct is_same<T, T> : public true_type
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
	template <class>
	struct __void_t
	{
		typedef void type;
	};
}

#endif