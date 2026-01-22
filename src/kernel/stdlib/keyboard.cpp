/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:17 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/22 17:46:39 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int	shortcutManger(unsigned char scancode, char *pressed, int nbpress) {
	if (nbpress == 2) {
		// Ctrl + Alt + [1-3] to switch terminal
		if ((scancode >= KEYBOARD_1 && scancode <= KEYBOARD_3) && pressed[KEYBOARD_CTRL]) {
			return TERMINAL_SWITCH_MASK | (scancode - KEYBOARD_1);
		}
	}
	return SHORTCUT_NONE;
}

void	pressPrint(Term *term, unsigned char scancode, bool maj) {
	if (maj)
		term->printk("%c", keyboardMaj_map[scancode]);
	else
		term->printk("%c", keyboard_map[scancode]);
}

int	keyboard_handler(Term *term) {
	unsigned char	scancode;
	static char		pressed[128];
	static int		nbpress = 0;
	static bool		maj = false;

	scancode = read_port(PS_2);
	if (scancode == KEYBOARD_ACK) {} // Ignore ACK from keyboard
	else if (!(scancode & UNPRESSED_MASK)) {
		if (!pressed[scancode])
			nbpress++;
		pressed[scancode] = 1;

		// Flush the PS/2 port
		write_port(PS_2, 0);
		
		if (!pressed[KEYBOARD_CTRL] && !pressed[KEYBOARD_ALT] && keyboard_map[scancode])
			pressPrint(term, scancode, maj);
		if (scancode == KEYBOARD_LEFTSHIFT || scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_CAPSLOCK)
			maj = !maj;
		return shortcutManger(scancode, pressed, nbpress);
	} else {
		// Remove the unpressed mask
		scancode &= ~UNPRESSED_MASK;
		
		if (pressed[scancode])
			nbpress--;
		pressed[scancode] = 0;
		
		if (scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_LEFTSHIFT)
			maj = !maj;

		// Flush the PS/2 port
		write_port(PS_2, 0);
	}
	return SHORTCUT_NONE;
}