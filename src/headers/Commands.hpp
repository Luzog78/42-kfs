/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:31:55 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 13:34:08 by bsavinel         ###   ########.fr       */
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
	int	hexdump(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);
}

#endif
