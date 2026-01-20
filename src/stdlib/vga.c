/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:14:23 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/20 17:46:48 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

uint16_t vga_color(uint8_t vga_fg, uint8_t vga_bg) {
	return vga_bg << 12 | vga_fg << 8;
}

uint16_t vga_char(uchar_t c, uint8_t vga_fg, uint8_t vga_bg) {
	return vga_bg << 12 | vga_fg << 8 | c;
}
