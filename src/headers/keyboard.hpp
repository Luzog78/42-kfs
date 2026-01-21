/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:01:09 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/21 17:00:01 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

extern "C" unsigned char read_port(int port);
extern "C" void write_port(int port, unsigned char data);
void keyboard_handler(Term *term);

extern unsigned char keyboard_map[128] ;

#endif