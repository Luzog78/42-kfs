/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:17 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/24 00:25:22 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int	handleShortcut(uint16_t scancode, bool *pressed, int nbpress) {
	if (nbpress == 2) {
		// Ctrl + [1-3] to switch terminal
		if ((pressed[KEY_1_L_CTRL] || pressed[KEY_1_R_CTRL])
				&& (scancode >= KEY_1_1 && scancode <= KEY_1_3)) {
			return FLAG_TERM_SWITCH | (scancode - KEY_1_1);
		}
	}
	return SHORTCUT_NONE;
}

void	handleTerminal(Term *term, uint16_t scancode, bool *pressed, bool caps) {
	if (pressed[KEY_1_L_CTRL] || pressed[KEY_1_R_CTRL])
		return;

	switch (scancode) {
		case KEY_1_ESC:
			term->setActive(false);
			VGA::hideCursor();
			return;

		case KEY_1_CURSOR_LEFT:
			term->moveCursor(-1, 0);
			term->scrollToCursor();
			return;
		
		case KEY_1_CURSOR_RIGHT:
			term->moveCursor(1, 0);
			term->scrollToCursor();
			return;

		case KEY_1_CURSOR_UP:
			term->moveCursor(0, -1);
			term->scrollToCursor();
			return;

		case KEY_1_CURSOR_DOWN:
			term->moveCursor(0, 1);
			term->scrollToCursor();
			return;
	}

	char	character = caps ? getUpperKey(scancode) : getLowerKey(scancode);
	if (character) {
		term->putc((char) character);
		term->scrollToCursor();
	}
}

int	handleKeyboard(Term *term) {
	static bool		pressed[384];
	static int		nbpress = 0;
	static bool		caps = false;
	static bool		capsLock = false;

	uint16_t		scancode = read_port(PS_2);
	if (scancode == KEYBOARD_ACK)
		return SHORTCUT_NONE;

	if (scancode == KEY_1_EXTENDED) {
		write_port(PS_2, 0); // Flush the PS/2 port
		while (read_port(PS_2) == KEYBOARD_ACK)
			/* Wait... */;
		scancode = 0x100 | read_port(PS_2);
	}

	write_port(PS_2, 0); // Flush the PS/2 port
	if (!(scancode & KEY_1_UNPRESSED_FLAG)) {
		if (!pressed[scancode])
			nbpress++;
		pressed[scancode] = true;

		if (scancode == KEY_1_L_SHIFT || scancode == KEY_1_R_SHIFT)
			caps = true;
		if (term)
			handleTerminal(term, scancode, pressed, caps || capsLock);
		return handleShortcut(scancode, pressed, nbpress);
	} else {
		scancode &= ~KEY_1_UNPRESSED_FLAG; // Remove the unpressed flag
		if (pressed[scancode])
			nbpress--;
		pressed[scancode] = false;

		if (scancode == KEY_1_CAPSLOCK)
			capsLock = !capsLock;
		else if (scancode == KEY_1_L_SHIFT || scancode == KEY_1_R_SHIFT)
			caps = false;
	}
	return SHORTCUT_NONE;
}
