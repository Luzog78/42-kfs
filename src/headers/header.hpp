/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/27 23:19:54 by luzog78          ###   ########.fr       */
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

extern "C" uint32_t	stack_guard;
extern "C" bool		stack_check(bool halt);
extern "C" uint8_t	read_port(uint16_t port);
extern "C" void		write_port(uint16_t port, uint8_t data);

#include "limits.hpp"
#include "string.hpp"
#include "Math.hpp"
#include "Vect2.hpp"
#include "VGA.hpp"
#include "Term.hpp"
#include "keyboard.hpp"
#include "demo.hpp"

#endif
