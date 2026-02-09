/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VGA.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:14:23 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 05:02:49 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace VGA {
	uint16_t	character(uint8_t vga_fg) {
		return vga_fg << 8;
	}

	uint16_t	character(uint8_t vga_fg, uint8_t vga_bg) {
		return vga_bg << 12 | vga_fg << 8;
	}

	uint16_t	character(uchar_t c, uint8_t vga_fg, uint8_t vga_bg) {
		return vga_bg << 12 | vga_fg << 8 | c;
	}

	uchar_t		getChar(uint8_t vga_char) {
		return vga_char & 0xFF;
	}

	uint16_t	getColor(uint8_t vga_char) {
		return vga_char & 0xFF00;
	}

	uint8_t		getFg(uint8_t vga_char) {
		return (vga_char >> 8) & 0xF;
	}

	uint8_t		getBg(uint8_t vga_char) {
		return (vga_char >> 12) & 0xF;
	}

	ssize_t	pos(ssize_t row, ssize_t col) {
		return row * VGA_WIDTH + col;
	}

	Vect2<ssize_t>	sop(ssize_t pos) {
		return Vect2<ssize_t>(pos % VGA_WIDTH, pos / VGA_WIDTH);
	}

	void	showCursor() {
		write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_START);
		write_port(VGA_REG_CRTC_DATA, read_port(VGA_REG_CRTC_DATA) & 0b11011111); // Bit 5: Cursor Disable
	}

	void	hideCursor() {
		write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_START);
		write_port(VGA_REG_CRTC_DATA, read_port(VGA_REG_CRTC_DATA) | 0b00100000); // Bit 5: Cursor Disable
	}

	void	moveCursor(ssize_t pos) {
		write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_HIGH);
		write_port(VGA_REG_CRTC_DATA, (pos >> 8) & 0xff);
		write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_LOW);
		write_port(VGA_REG_CRTC_DATA, pos & 0xff);
	}

	void	moveCursor(size_t row, size_t col) {
		moveCursor(pos(row, col));
	}

	void	debug(ssize_t pos, const char *msg, uint16_t color) {
		for (size_t i = 0; msg[i]; i++)
			((uint16_t *) VGA_MEMORY)[pos + i] = msg[i] | color;
	}

	void	fill(uint16_t character) {
		for (size_t i = 0; i < VGA_SIZE; i++)
			((uint16_t *) VGA_MEMORY)[i] = character;
	}
}
