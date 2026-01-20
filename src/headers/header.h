/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/20 17:46:38 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_SIZE	2000
#define VGA_MEMORY	0xB8000
#define TERM_PTR	((uint16_t *) VGA_MEMORY)
#define VGA_OFFSET(row, col)	((row) * VGA_WIDTH + (col))

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

typedef char				int8_t;
typedef short				int16_t;
typedef int					int32_t;
typedef long long			int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;
typedef uint64_t			size_t;
typedef unsigned char		uchar_t;

size_t		strlen(const char *str);

uint16_t	vga_char(uint8_t c, uint8_t vga_fg, uint8_t vga_bg);
uint16_t	vga_color(uint8_t vga_fg, uint8_t vga_bg);

void		term_write(uint16_t *vga_char, size_t len, size_t offset);
void		term_putc(uchar_t c, uint16_t color, size_t offset);
void		term_put(const char *str, uint16_t color, size_t offset);
void		term_fill(uint16_t vga_char);

#endif
