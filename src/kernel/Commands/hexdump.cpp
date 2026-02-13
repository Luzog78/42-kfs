/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:34:59 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/13 16:45:07 by luzog78          ###   ########.fr       */
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

		int64_t	addr = string::xtoull(argv[1]);
		int64_t	size = string::atoll(argv[2]);
		if (size <= 0 || addr < 0
				|| addr > UINT32_MAX || size > UINT32_MAX
				|| addr + size > UINT32_MAX) {
			prompt->put("Bad value\n");
			return 1;
		}
		prompt->hexdump((ptr_t) addr, size);
		return 0;
	}
}
