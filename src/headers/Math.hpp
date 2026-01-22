/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 02:48:54 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 07:25:58 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
#define MATH_HPP

#include "header.hpp"

class Math {
	public:
		template<typename T>
		static T	clamp(const T val, const T min, const T max) {
			if (val < min)
				return min;
			if (val > max)
				return max;
			return val;
		}

		template<typename T>
		static T	min(const T a, const T b) {
			return (a < b) ? a : b;
		}

		template<typename T>
		static T	max(const T a, const T b) {
			return (a > b) ? a : b;
		}
};

#endif
