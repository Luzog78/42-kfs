/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:34:59 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/13 14:37:17 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace Commands {
	int	hexdump(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv) {
		(void) cmdLine;
		
		if (argc != 3) {
			prompt->put("Usage: hexdump [memory] [size]\n");
			return 1;
		}

		unsigned int addr;
		size_t		size;

		addr = string::hexStringToInt(argv[1]);
		size = string::atosize_t(argv[2]);

		if (size == 0 || addr > UINT32_MAX || size > UINT32_MAX || addr + size > UINT32_MAX) {
			prompt->put("Bad value\n");
			return 1;
		}	
		
		prompt->hexdump((void *)addr, size);
		return 0;
	}
}