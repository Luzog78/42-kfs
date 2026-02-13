/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:36:06 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 03:37:58 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace Commands {
	int shutdown(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv) {
		(void) cmdLine;

		int64_t	delay = 0;
		if (argc > 1) {
			delay = string::atoll(argv[1]);
			if (delay < 0) {
				prompt->put("Invalid delay value.\n");
				return 1;
			}
		}

		prompt->put("Shutting down...\n");
		for (int i = 0; i < 1000; i++)
			for (int64_t d = 0; d < delay; d++)
				asm volatile("nop"); // Sleep
		shutdown_system();
		return 0;
	}
}
