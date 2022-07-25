/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:45:43 by mcha              #+#    #+#             */
/*   Updated: 2022/07/25 22:08:53 by mcha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <bool Cond, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { typedef T type; };

template <typename T>
void fnc(const T &t,
         typename enable_if<std::is_integral<T>::value>::type * = 0) {
    std::cout << t << std::endl;
    std::cout << "run fnc" << std::endl;
}

template <typename T> void fnc(const T &t) {
    std::cout << t << std::endl;
    std::cout << "fail fnc" << std::endl;
}

int main(void) {
    fnc(1);
    return (0);
}