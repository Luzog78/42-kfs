/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:36:06 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 03:07:16 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace Commands {
	int	echo(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv) {
		(void) cmdLine;

		size_t	i = 1;
		bool	nFlag = false;

		for (; i < argc && argv[i][0] == '-'; i++) {
			if (argv[i][1] != 'n')
				break;
			size_t	j = 2;
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] != '\0')
				break;
			nFlag = true;
		}
		if (i < argc)
			prompt->put(argv[i++]);
		for (; i < argc; i++)
			prompt->printk(" %s", argv[i]);
		if (!nFlag)
			prompt->putc('\n');
		return 0;
	}
}
