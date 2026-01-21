/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/21 09:55:11 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"


extern "C" int main(void) {
	Term	term(VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY));

	term.clear();

	term.put("Hello, Kernel World!\n\n");

	term.put("Here is every supported chars: ");
	term.setColor(VGA::character(VGA_C_GREEN, VGA_C_DARK_GREY));
	for (uchar_t c = 32; c < 160; c++)
		if (c != 127)
			term.putc((char) c);

	while (1)
		asm volatile ("hlt");
	return 0;
}
