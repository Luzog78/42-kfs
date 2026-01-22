/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:17 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/22 14:04:24 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int shortcutManger(Term *term, unsigned char scancode, char *pressed, int nbpress)
{
	if (nbpress == 3)
	{
		if (scancode == 0x12 && pressed[KEYBOARD_ALT] && pressed[KEYBOARD_CTRL])
		{
			term->printk("\nRacourci ctrl + alt + e\n");
			return SHORTCUT_CTRL_ALT_E;
		}
	}
	return SHORTCUT_NONE;
}

void pressPrint(Term *term, unsigned char scancode, bool maj)
{
	if (maj)
		term->printk("%c", keyboardMaj_map[scancode]);
	else
		term->printk("%c", keyboard_map[scancode]);
}

int keyboard_handler(Term *term)
{
	unsigned char scancode;
	static char pressed[128];
	static int nbpress = 0;
	static bool maj = false;

	scancode = read_port(0x60);

	if (scancode == 250) {} // Ignore ACK from keyboard
	else if (!(scancode & 0x80))
	{
		if (!pressed[scancode])
			nbpress++;
		pressed[scancode] = 1;
		write_port(0x60, 0);
		if (!pressed[KEYBOARD_CTRL] && !pressed[KEYBOARD_ALT] && keyboard_map[scancode])
			pressPrint(term, scancode, maj);

		if (scancode == KEYBOARD_LEFTSHIFT || scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_CAPSLOCK)
			maj = !maj;

		return shortcutManger(term, scancode, pressed, nbpress);
	}
	else
	{
		// Remove the unpressed flag
		scancode &= ~0x80;

		if (pressed[scancode])
			nbpress--;
		pressed[scancode] = 0;

		if (scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_LEFTSHIFT)
			maj = !maj;
		write_port(0x60, 0);
	}
	return SHORTCUT_NONE;
}