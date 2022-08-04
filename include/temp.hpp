/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:25:34 by mcha              #+#    #+#             */
/*   Updated: 2022/08/04 18:47:00 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_HPP
#define TEMP_HPP

namespace temp
{
	template <typename _Iter, bool>
	struct __iterator_traits_impl
	{
		static const int a = 1;
	};

	template <typename _Iter>
	struct __iterator_traits_impl<_Iter, true>
	{
		static const int a = 2;
	};
}

#endif