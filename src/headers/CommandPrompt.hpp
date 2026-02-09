/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrompt.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:22:57 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 03:40:20 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PROMPT_HPP
#define COMMAND_PROMPT_HPP

#include "header.hpp"

/** Including null terminator. */
#define	CMD_MAX_LEN		256
/** Including null terminator. */
#define	CMD_MAX_ARGS	16
#define	CMD_PREFIX		"[%d] $> ", _lastResult

class CommandPrompt;
typedef int	(*cmd_func_t)(CommandPrompt *prompt, char *cmdLine, size_t argc, char **argv);

class CommandPrompt : public Term {
	private:
		char	_cmd[CMD_MAX_LEN] = {0};
		size_t	_cmdCursor = 0;
		int		_lastResult = 0;

		Vect2<size_t>	_cmdRenderStart = Vect2<size_t>(0, 0);
		Vect2<size_t>	_cmdRenderEnd = Vect2<size_t>(0, 0);

		void	_init();

	public:
		static cmd_func_t	getCommandFunc(const char *cmd);

		CommandPrompt();
		CommandPrompt(const CommandPrompt &other);
		CommandPrompt(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor);
		CommandPrompt(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor, size_t histHeight);

		CommandPrompt	&operator=(const CommandPrompt &other);
		~CommandPrompt();

		void	onKeyDown(uint16_t scancode, bool *pressed, bool caps) override;
		void	updateVGACursor();

		/** Clear the command line from the terminal */
		void	eraseCommand();
		/** Flushes the command line */
		void	flushCommand();
		/** Erases and flushes the command line, then update the VGA cursor */
		void	refreshCommand();
		/** Resets every field */
		void	resetCommand();

		int	executeCommand();
		int	executeCommand(char *cmdLine);
};

#endif
