/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 17:17:54 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

#define NULL				((void *) 0)

typedef char				int8_t;
typedef short				int16_t;
typedef int					int32_t;
typedef long long			int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;
typedef uint64_t			size_t;
typedef int64_t				ssize_t;
typedef unsigned char		uchar_t;
typedef void				*ptr_t;

struct gdt_ptr_s {
	uint16_t limit;
	uint32_t base;
}	__attribute__((packed));

extern "C" uint32_t	stack_guard;
extern "C" bool		stack_check(bool halt);
extern "C" uint8_t	read_port(uint16_t port);
extern "C" void		write_port(uint16_t port, uint8_t data);
extern "C" void		reboot_system();
extern "C" void		shutdown_system();
extern "C" void		gdt_get_location(struct gdt_ptr_s* out);
extern "C" void		gdt_set_location(uint32_t limit, uint32_t base);
extern "C" void		gdt_reload_segments();

/** 42 KFS Header */
extern const char *__42__[13];

#include "limits.hpp"
#include "string.hpp"
#include "Math.hpp"
#include "Vect2.hpp"
#include "VGA.hpp"
#include "Term.hpp"
#include "keyboard.hpp"
#include "demo.hpp"
#include "Gdt.hpp"
#include "CommandPrompt.hpp"
#include "Commands.hpp"

#endif
