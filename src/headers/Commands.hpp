/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:31:55 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 04:37:48 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "header.hpp"

namespace Commands {
	int	echo(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);
	int	reboot(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);
	int	shutdown(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);
	int	demo(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);
}

#endif
