/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VGA.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:14:51 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 02:15:31 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VGA_HPP
#define VGA_HPP

#include "header.hpp"

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_SIZE	2000
#define VGA_MEMORY	0xb8000

/** http://www.osdever.net/FreeVGA/vga/vga.htm#register */
#define VGA_REG_CRTC_INDEX			0x3d4
/** http://www.osdever.net/FreeVGA/vga/crtcreg.htm */
#define VGA_REG_CRTC_DATA			0x3d5
/** http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A */
#define VGA_REG_CRTC_CURSOR_START	0x0a
/** http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0B */
#define VGA_REG_CRTC_CURSOR_END		0x0b
/** http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0E */
#define VGA_REG_CRTC_CURSOR_HIGH	0x0e
/** http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0F */
#define VGA_REG_CRTC_CURSOR_LOW		0x0f

#define VGA_C_BLACK			0x0
#define VGA_C_BLUE			0x1
#define VGA_C_GREEN			0x2
#define VGA_C_CYAN			0x3
#define VGA_C_RED			0x4
#define VGA_C_MAGENTA		0x5
#define VGA_C_BROWN			0x6
#define VGA_C_LIGHT_GREY	0x7
#define VGA_C_DARK_GREY		0x8
#define VGA_C_LIGHT_BLUE	0x9
#define VGA_C_LIGHT_GREEN	0xa
#define VGA_C_LIGHT_CYAN	0xb
#define VGA_C_LIGHT_RED		0xc
#define VGA_C_LIGHT_MAGENTA	0xd
#define VGA_C_LIGHT_BROWN	0xe
#define VGA_C_WHITE			0xf

class VGA {
	public:
		static uint16_t			character(uint8_t vga_fg);
		static uint16_t			character(uint8_t vga_fg, uint8_t vga_bg);
		static uint16_t			character(uchar_t c, uint8_t vga_fg, uint8_t vga_bg);

		static uchar_t			getChar(uint8_t vga_char);
		static uint16_t			getColor(uint8_t vga_char);
		static uint8_t			getFg(uint8_t vga_char);
		static uint8_t			getBg(uint8_t vga_char);

		static ssize_t			pos(ssize_t row, ssize_t col);
		static Vect2<ssize_t>	sop(ssize_t pos);

		static void				showCursor();
		static void				hideCursor();
		static void				moveCursor(ssize_t pos);
		static void				moveCursor(size_t row, size_t col);
};

#endif
