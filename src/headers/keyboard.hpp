/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:01:09 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/24 00:35:03 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#define SHORTCUT_NONE			0
#define FLAG_TERM_SWITCH		0x10

int								handleKeyboard(Term *term);

/**
 * See https://wiki.osdev.org/PS/2_Keyboard
 */
#define PS_2					0x60
/**
 * After each scan, we write as acknowledgment.
 * The next reads will result in `0xfa` if PS_2 hasn't acknowledged our acknowledgment.
 */
#define KEYBOARD_ACK			0xfa

/**
 * Extended keys (R_CTRL, PLAY, POWER, ...) begin by `0xe0`.
 * When we receive `0xe0`, the next byte will be the actual
 *  key code from the extended key set.
 * See https://wiki.osdev.org/PS/2_Keyboard#Scan_Code_Set_1
 */
#define KEY_1_EXTENDED			0xe0
/**
 * `0x80 = 0b1000_0000` | Bit 8: `0` -> Pressed; `1` -> Unpressed
 * See https://wiki.osdev.org/PS/2_Keyboard#Scan_Code_Set_1
 */
#define KEY_1_UNPRESSED_FLAG	0x80
#define KEY_1_ESC				0x01
#define KEY_1_1					0x02
#define KEY_1_2					0x03
#define KEY_1_3					0x04
#define KEY_1_4					0x05
#define KEY_1_5					0x06
#define KEY_1_6					0x07
#define KEY_1_7					0x08
#define KEY_1_8					0x09
#define KEY_1_9					0x0a
#define KEY_1_0					0x0b
#define KEY_1_MINUS				0x0c
#define KEY_1_EQUA				0x0d
#define KEY_1_BACKSPACE			0x0e
#define KEY_1_TAB				0x0f
#define KEY_1_Q					0x10
#define KEY_1_W					0x11
#define KEY_1_E					0x12
#define KEY_1_R					0x13
#define KEY_1_T					0x14
#define KEY_1_Y					0x15
#define KEY_1_U					0x16
#define KEY_1_I					0x17
#define KEY_1_O					0x18
#define KEY_1_P					0x19
#define KEY_1_LEFT_BRACKET		0x1a
#define KEY_1_RIGHT_BRACKET		0x1b
#define KEY_1_ENTER				0x1c
#define KEY_1_L_CTRL			0x1d
#define KEY_1_A					0x1e
#define KEY_1_S					0x1f
#define KEY_1_D					0x20
#define KEY_1_F					0x21
#define KEY_1_G					0x22
#define KEY_1_H					0x23
#define KEY_1_J					0x24
#define KEY_1_K					0x25
#define KEY_1_L					0x26
#define KEY_1_SEMICOLON			0x27
#define KEY_1_QUOTE				0x28
#define KEY_1_GRAVE				0x29
#define KEY_1_L_SHIFT			0x2a
#define KEY_1_BACKSLASH			0x2b
#define KEY_1_Z					0x2c
#define KEY_1_X					0x2d
#define KEY_1_C					0x2e
#define KEY_1_V					0x2f
#define KEY_1_B					0x30
#define KEY_1_N					0x31
#define KEY_1_M					0x32
#define KEY_1_COMMA				0x33
#define KEY_1_DOT				0x34
#define KEY_1_SLASH				0x35
#define KEY_1_R_SHIFT			0x36
#define KEY_1_KP_ASTERISK		0x37
#define KEY_1_L_ALT				0x38
#define KEY_1_SPACE				0x39
#define KEY_1_CAPSLOCK			0x3a
#define KEY_1_F1				0x3b
#define KEY_1_F2				0x3c
#define KEY_1_F3				0x3d
#define KEY_1_F4				0x3e
#define KEY_1_F5				0x3f
#define KEY_1_F6				0x40
#define KEY_1_F7				0x41
#define KEY_1_F8				0x42
#define KEY_1_F9				0x43
#define KEY_1_F10				0x44
#define KEY_1_NUMLOCK			0x45
#define KEY_1_SCROLLLOCK		0x46
#define KEY_1_KP_7				0x47
#define KEY_1_KP_8				0x48
#define KEY_1_KP_9				0x49
#define KEY_1_KP_MINUS			0x4a
#define KEY_1_KP_4				0x4b
#define KEY_1_KP_5				0x4c
#define KEY_1_KP_6				0x4d
#define KEY_1_KP_PLUS			0x4e
#define KEY_1_KP_1				0x4f
#define KEY_1_KP_2				0x50
#define KEY_1_KP_3				0x51
#define KEY_1_KP_0				0x52
#define KEY_1_KP_DOT			0x53
#define KEY_1_F11				0x57
#define KEY_1_F12				0x58
#define KEY_1_PREV_TRACK		0x110
#define KEY_1_NEXT_TRACK		0x119
#define KEY_1_KP_ENTER			0x11c
#define KEY_1_R_CTRL			0x11d
#define KEY_1_MUTE				0x120
#define KEY_1_CALC				0x121
#define KEY_1_PLAY				0x122
#define KEY_1_STOP				0x124
#define KEY_1_VOL_DOWN			0x12e
#define KEY_1_VOL_UP			0x130
#define KEY_1_WWW_HOME			0x132
#define KEY_1_KP_SLASH			0x135
#define KEY_1_R_ALT				0x138
#define KEY_1_HOME				0x147
#define KEY_1_CURSOR_UP			0x148
#define KEY_1_PAGE_UP			0x149
#define KEY_1_CURSOR_LEFT		0x14b
#define KEY_1_CURSOR_RIGHT		0x14d
#define KEY_1_END				0x14f
#define KEY_1_CURSOR_DOWN		0x150
#define KEY_1_PAGE_DOWN			0x151
#define KEY_1_INSERT			0x152
#define KEY_1_DELETE			0x153
#define KEY_1_L_GUI				0x15b
#define KEY_1_R_GUI				0x15c
#define KEY_1_APPS				0x15d
#define KEY_1_POWER				0x15e
#define KEY_1_SLEEP				0x15f
#define KEY_1_WAKE				0x163
#define KEY_1_WWW_SEARCH		0x165
#define KEY_1_WWW_FAV			0x166
#define KEY_1_WWW_REFRESH		0x167
#define KEY_1_WWW_STOP			0x168
#define KEY_1_WWW_FORWARD		0x169
#define KEY_1_WWW_BACK			0x16a
#define KEY_1_MY_COMPUTER		0x16b
#define KEY_1_EMAIL				0x16c
#define KEY_1_MEDIA_SELECT		0x16d

constexpr char getLowerKey(uint16_t scancode) {
	switch (scancode) {
		case KEY_1_1:				return '1';
		case KEY_1_2:				return '2';
		case KEY_1_3:				return '3';
		case KEY_1_4:				return '4';
		case KEY_1_5:				return '5';
		case KEY_1_6:				return '6';
		case KEY_1_7:				return '7';
		case KEY_1_8:				return '8';
		case KEY_1_9:				return '9';
		case KEY_1_0:				return '0';
		case KEY_1_MINUS:			return '-';
		case KEY_1_EQUA:			return '=';
		case KEY_1_BACKSPACE:		return '\b';
		case KEY_1_TAB:				return '\t';
		case KEY_1_Q:				return 'q';
		case KEY_1_W:				return 'w';
		case KEY_1_E:				return 'e';
		case KEY_1_R:				return 'r';
		case KEY_1_T:				return 't';
		case KEY_1_Y:				return 'y';
		case KEY_1_U:				return 'u';
		case KEY_1_I:				return 'i';
		case KEY_1_O:				return 'o';
		case KEY_1_P:				return 'p';
		case KEY_1_LEFT_BRACKET:	return '[';
		case KEY_1_RIGHT_BRACKET:	return ']';
		case KEY_1_ENTER:			return '\n';
		case KEY_1_A:				return 'a';
		case KEY_1_S:				return 's';
		case KEY_1_D:				return 'd';
		case KEY_1_F:				return 'f';
		case KEY_1_G:				return 'g';
		case KEY_1_H:				return 'h';
		case KEY_1_J:				return 'j';
		case KEY_1_K:				return 'k';
		case KEY_1_L:				return 'l';
		case KEY_1_SEMICOLON:		return ';';
		case KEY_1_QUOTE:			return '\'';
		case KEY_1_GRAVE:			return '`';
		case KEY_1_BACKSLASH:		return '\\';
		case KEY_1_Z:				return 'z';
		case KEY_1_X:				return 'x';
		case KEY_1_C:				return 'c';
		case KEY_1_V:				return 'v';
		case KEY_1_B:				return 'b';
		case KEY_1_N:				return 'n';
		case KEY_1_M:				return 'm';
		case KEY_1_COMMA:			return ',';
		case KEY_1_DOT:				return '.';
		case KEY_1_SLASH:			return '/';
		case KEY_1_KP_ASTERISK:		return '*';
		case KEY_1_SPACE:			return ' ';
		case KEY_1_KP_7:			return '7';
		case KEY_1_KP_8:			return '8';
		case KEY_1_KP_9:			return '9';
		case KEY_1_KP_MINUS:		return '-';
		case KEY_1_KP_4:			return '4';
		case KEY_1_KP_5:			return '5';
		case KEY_1_KP_6:			return '6';
		case KEY_1_KP_PLUS:			return '+';
		case KEY_1_KP_1:			return '1';
		case KEY_1_KP_2:			return '2';
		case KEY_1_KP_3:			return '3';
		case KEY_1_KP_0:			return '0';
		case KEY_1_KP_DOT:			return '.';
		case KEY_1_KP_ENTER:		return '\n';
		case KEY_1_KP_SLASH:		return '/';
		default:					return 0;
	}
};

constexpr char getUpperKey(uint16_t scancode) {
	switch (scancode) {
		case KEY_1_1:				return '!';
		case KEY_1_2:				return '@';
		case KEY_1_3:				return '#';
		case KEY_1_4:				return '$';
		case KEY_1_5:				return '%';
		case KEY_1_6:				return '^';
		case KEY_1_7:				return '&';
		case KEY_1_8:				return '*';
		case KEY_1_9:				return '(';
		case KEY_1_0:				return ')';
		case KEY_1_MINUS:			return '_';
		case KEY_1_EQUA:			return '+';
		case KEY_1_BACKSPACE:		return '\b';
		case KEY_1_TAB:				return '\t';
		case KEY_1_Q:				return 'Q';
		case KEY_1_W:				return 'W';
		case KEY_1_E:				return 'E';
		case KEY_1_R:				return 'R';
		case KEY_1_T:				return 'T';
		case KEY_1_Y:				return 'Y';
		case KEY_1_U:				return 'U';
		case KEY_1_I:				return 'I';
		case KEY_1_O:				return 'O';
		case KEY_1_P:				return 'P';
		case KEY_1_LEFT_BRACKET:	return '{';
		case KEY_1_RIGHT_BRACKET:	return '}';
		case KEY_1_ENTER:			return '\n';
		case KEY_1_A:				return 'A';
		case KEY_1_S:				return 'S';
		case KEY_1_D:				return 'D';
		case KEY_1_F:				return 'F';
		case KEY_1_G:				return 'G';
		case KEY_1_H:				return 'H';
		case KEY_1_J:				return 'J';
		case KEY_1_K:				return 'K';
		case KEY_1_L:				return 'L';
		case KEY_1_SEMICOLON:		return ':';
		case KEY_1_QUOTE:			return '"';
		case KEY_1_GRAVE:			return '~';
		case KEY_1_BACKSLASH:		return '|';
		case KEY_1_Z:				return 'Z';
		case KEY_1_X:				return 'X';
		case KEY_1_C:				return 'C';
		case KEY_1_V:				return 'V';
		case KEY_1_B:				return 'B';
		case KEY_1_N:				return 'N';
		case KEY_1_M:				return 'M';
		case KEY_1_COMMA:			return '<';
		case KEY_1_DOT:				return '>';
		case KEY_1_SLASH:			return '?';
		case KEY_1_KP_ASTERISK:		return '*';
		case KEY_1_SPACE:			return ' ';
		case KEY_1_KP_7:			return '7';
		case KEY_1_KP_8:			return '8';
		case KEY_1_KP_9:			return '9';
		case KEY_1_KP_MINUS:		return '-';
		case KEY_1_KP_4:			return '4';
		case KEY_1_KP_5:			return '5';
		case KEY_1_KP_6:			return '6';
		case KEY_1_KP_PLUS:			return '+';
		case KEY_1_KP_1:			return '1';
		case KEY_1_KP_2:			return '2';
		case KEY_1_KP_3:			return '3';
		case KEY_1_KP_0:			return '0';
		case KEY_1_KP_DOT:			return '.';
		case KEY_1_KP_ENTER:		return '\n';
		case KEY_1_KP_SLASH:		return '/';
		default:					return 0;
	}
};

#endif
