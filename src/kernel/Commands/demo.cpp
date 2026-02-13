/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:36:06 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 16:45:33 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace Commands {
	int	demo(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv) {
		(void) cmdLine;

		if (argc < 2) {
			prompt->put("Usage: demo <no>\n");
			return 1;
		}

		__DEMO_NO__ = (int) string::atoll(argv[1]);
		__DEMO_RUN__ = false;
		prompt->put("Switching to demo %d...\n", __DEMO_NO__);
		return 0;
	}
}
