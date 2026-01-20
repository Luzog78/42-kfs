/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:37 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/20 17:52:13 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	term_write(uint16_t *vga_char, size_t len, size_t offset) {
	for (size_t i = 0; i < len; i++)
		TERM_PTR[offset + i] = vga_char[i];
}

void	term_putc(uchar_t c, uint16_t color, size_t offset) {
	TERM_PTR[offset] = c | color;
}

void	term_put(const char *str, uint16_t color, size_t offset) {
	for (size_t i = 0; str[i]; i++)
		TERM_PTR[offset + i] = (uchar_t) str[i] | color;
}

void	term_fill(uint16_t vga_char) {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		TERM_PTR[i] = vga_char;
}
