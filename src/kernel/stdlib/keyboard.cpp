/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:17 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/21 17:02:34 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

void keyboard_handler(Term *term)
{
	unsigned char scancode;

	scancode = read_port(0x60);

	if (!(scancode & 0x80))
	{
		term->putc((char)keyboard_map[scancode]);
		write_port(0x60, 0);
	}
}