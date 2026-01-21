/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/21 15:38:00 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

extern "C" int main(void) {
	Term	term(VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY));

	term.clear();

	term.put("Hello, Kernel World!\n\n");
	term.printk("This is a string: %c\n", 'c');
	while (1)
		asm volatile ("hlt");
	return 0;
}
