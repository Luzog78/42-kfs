/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:01:09 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/22 16:43:54 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

extern "C" unsigned char	read_port(int port);
extern "C" void				write_port(int port, unsigned char data);
int							keyboard_handler(Term *term);

extern unsigned char keyboard_map[128];
extern unsigned char keyboardMaj_map[128];

#define PS_2 0x60
#define KEYBOARD_ACK 250
#define UNPRESSED_MASK 0x80

#define KEYBOARD_CAPSLOCK	0x3a
#define KEYBOARD_LEFTSHIFT	0x2a
#define KEYBOARD_RIGHTSHIFT	0x36
#define KEYBOARD_CTRL		0x1d
#define KEYBOARD_ALT		0x38
#define KEYBOARD_1			0x2
#define KEYBOARD_2			0x3
#define KEYBOARD_3			0x4

#define SHORTCUT_NONE		0
#define TERMINAL_SWITCH_MASK 16

#endif