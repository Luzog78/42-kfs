/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VGA.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:14:51 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 08:24:13 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VGA_HPP
#define VGA_HPP

#include "header.hpp"

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_SIZE	2000
#define VGA_MEMORY	0xb8000

#define VGA_C_BLACK			0
#define VGA_C_BLUE			1
#define VGA_C_GREEN			2
#define VGA_C_CYAN			3
#define VGA_C_RED			4
#define VGA_C_MAGENTA		5
#define VGA_C_BROWN			6
#define VGA_C_LIGHT_GREY	7
#define VGA_C_DARK_GREY		8
#define VGA_C_LIGHT_BLUE	9
#define VGA_C_LIGHT_GREEN	10
#define VGA_C_LIGHT_CYAN	11
#define VGA_C_LIGHT_RED		12
#define VGA_C_LIGHT_MAGENTA	13
#define VGA_C_LIGHT_BROWN	14
#define VGA_C_WHITE			15

class VGA {
	public:
		static uint16_t			character(uint8_t vga_bg);
		static uint16_t			character(uint8_t vga_fg, uint8_t vga_bg);
		static uint16_t			character(uchar_t c, uint8_t vga_fg, uint8_t vga_bg);

		static uchar_t			getChar(uint8_t vga_char);
		static uint16_t			getColor(uint8_t vga_char);
		static uint8_t			getFg(uint8_t vga_char);
		static uint8_t			getBg(uint8_t vga_char);

		static ssize_t			pos(ssize_t row, ssize_t col);
		static Vect2<ssize_t>	sop(ssize_t pos);
};

#endif
