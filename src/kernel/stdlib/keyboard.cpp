/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:17 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/23 13:18:35 by luzog78          ###   ########.fr       */
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

void	pressPrint(Term *term, unsigned char scancode, bool caps) {
	if (caps)
		term->putc((char) upperKeyboardMap[scancode]);
	else
		term->putc((char) keyboardMap[scancode]);
	term->scrollToCursor();
}

int	keyboardHandler(Term *term) {
	unsigned char	scancode;
	static char		pressed[128];
	static int		nbpress = 0;
	static bool		caps = false;

	scancode = read_port(PS_2);
	if (scancode == KEYBOARD_ACK) {
		// Ignore ACK from keyboard
	} else if (!(scancode & UNPRESSED_MASK)) {
		if (!pressed[scancode])
			nbpress++;
		pressed[scancode] = 1;

		write_port(PS_2, 0); // Flush the PS/2 port
		
		if (!pressed[KEYBOARD_CTRL] && !pressed[KEYBOARD_ALT] && keyboardMap[scancode])
			pressPrint(term, scancode, caps);
		if (scancode == KEYBOARD_LEFTSHIFT || scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_CAPSLOCK)
			caps = !caps;
		return shortcutManger(scancode, pressed, nbpress);
	} else {
		scancode &= ~UNPRESSED_MASK; // Remove the unpressed mask

		if (pressed[scancode])
			nbpress--;
		pressed[scancode] = 0;

		if (scancode == KEYBOARD_RIGHTSHIFT || scancode == KEYBOARD_LEFTSHIFT)
			caps = !caps;

		write_port(PS_2, 0); // Flush the PS/2 port
	}
	return SHORTCUT_NONE;
}
