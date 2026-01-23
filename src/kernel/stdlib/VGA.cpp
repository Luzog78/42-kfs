/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VGA.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:14:23 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/23 14:13:46 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

uint16_t	VGA::character(uint8_t vga_bg) {
	return vga_bg << 12;
}

uint16_t	VGA::character(uint8_t vga_fg, uint8_t vga_bg) {
	return vga_bg << 12 | vga_fg << 8;
}

uint16_t	VGA::character(uchar_t c, uint8_t vga_fg, uint8_t vga_bg) {
	return vga_bg << 12 | vga_fg << 8 | c;
}

uchar_t		VGA::getChar(uint8_t vga_char) {
	return vga_char & 0xFF;
}

uint16_t	VGA::getColor(uint8_t vga_char) {
	return vga_char & 0xFF00;
}

uint8_t		VGA::getFg(uint8_t vga_char) {
	return (vga_char >> 8) & 0xF;
}

uint8_t		VGA::getBg(uint8_t vga_char) {
	return (vga_char >> 12) & 0xF;
}

ssize_t	VGA::pos(ssize_t row, ssize_t col) {
	return row * VGA_WIDTH + col;
}

Vect2<ssize_t>	VGA::sop(ssize_t pos) {
	return Vect2<ssize_t>(pos % VGA_WIDTH, pos / VGA_WIDTH);
}

void	VGA::showCursor() {
	write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_START);
	write_port(VGA_REG_CRTC_DATA, read_port(VGA_REG_CRTC_DATA) & 0b11011111); // Bit 5: Cursor Disable
}

void	VGA::hideCursor() {
	write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_START);
	write_port(VGA_REG_CRTC_DATA, read_port(VGA_REG_CRTC_DATA) | 0b00100000); // Bit 5: Cursor Disable
}

void	VGA::moveCursor(ssize_t pos) {
	write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_HIGH);
	write_port(VGA_REG_CRTC_DATA, (pos >> 8) & 0xff);
	write_port(VGA_REG_CRTC_INDEX, VGA_REG_CRTC_CURSOR_LOW);
	write_port(VGA_REG_CRTC_DATA, pos & 0xff);
}

void	VGA::moveCursor(size_t row, size_t col) {
	moveCursor(pos(row, col));
}
