/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:30:22 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/20 19:37:41 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include "header.hpp"

template <typename T>
class Vect2 {
	public:
		T x;
		T y;

		Vect2() : x(T()), y(T()) {};
		Vect2(T x, T y) : x(x), y(y) {};
		Vect2(const Vect2 &other) : x(other.x), y(other.y) {};
		Vect2 &operator=(const Vect2 &other) {
			if (this != &other) {
				x = other.x;
				y = other.y;
			}
			return *this;
		};
		~Vect2() {};

		template<typename U>
		Vect2 operator+(const Vect2<U> &other) const {
			return Vect2(x + other.x, y + other.y);
		};

		template<typename U>
		Vect2 operator-(const Vect2<U> &other) const {
			return Vect2(x - other.x, y - other.y);
		};

		template<typename U>
		Vect2 operator*(const Vect2<U> &other) const {
			return Vect2(x * other.x, y * other.y);
		};

		template<typename U>
		Vect2 operator*(const U &scalar) const {
			return Vect2(x * scalar, y * scalar);
		};

		template<typename U>
		Vect2 operator/(const Vect2<U> &other) const {
			return Vect2(x / other.x, y / other.y);
		};

		template<typename U>
		Vect2 operator/(const U &scalar) const {
			return Vect2(x / scalar, y / scalar);
		};

		Vect2 clone() const {
			return Vect2(x, y);
		};
};

#endif
