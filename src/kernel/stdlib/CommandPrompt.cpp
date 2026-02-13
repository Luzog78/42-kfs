/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrompt.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:37 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 04:48:46 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

CommandPrompt::CommandPrompt() :
		Term() {
	_init();
}

CommandPrompt::CommandPrompt(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor) :
		Term(size, renderPos, vgaColor) {
	_init();
}

CommandPrompt::CommandPrompt(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor, size_t histHeight) :
		Term(size, renderPos, vgaColor, histHeight) {
	_init();
}

CommandPrompt::CommandPrompt(const CommandPrompt &other) :
		Term(other),
		_cmdCursor(other._cmdCursor),
		_cmdRenderStart(other._cmdRenderStart),
		_cmdRenderEnd(other._cmdRenderEnd) {
	for (size_t i = 0; i < CMD_MAX_LEN; i++)
		_cmd[i] = other._cmd[i];
}

CommandPrompt	&CommandPrompt::operator=(const CommandPrompt &other) {
	if (this != &other) {
		Term::operator=(other);
		for (size_t i = 0; i < CMD_MAX_LEN; i++)
			_cmd[i] = other._cmd[i];
		_cmdCursor = other._cmdCursor;
		_cmdRenderStart = other._cmdRenderStart;
		_cmdRenderEnd = other._cmdRenderEnd;
	}
	return *this;
}

CommandPrompt::~CommandPrompt() {}


/* ************************************************************************** */

cmd_func_t CommandPrompt::getCommandFunc(const char *cmd) {
	if (!string::strcmp(cmd, "echo"))
		return (cmd_func_t) Commands::echo;
	if (!string::strcmp(cmd, "reboot"))
		return (cmd_func_t) Commands::reboot;
	if (!string::strcmp(cmd, "shutdown"))
		return (cmd_func_t) Commands::shutdown;
	if (!string::strcmp(cmd, "demo"))
		return (cmd_func_t) Commands::demo;
	return 0;
}

void	CommandPrompt::_init() {
	for (size_t i = 0; i < CMD_MAX_LEN; i++)
		_cmd[i] = 0;
	_cmdCursor = 0;
	_lastResult = 0;
	_cmdRenderStart = _cur.clone();
	_cmdRenderEnd = _cur.clone();
}

void	CommandPrompt::onKeyDown(uint16_t scancode, bool *pressed, bool caps) {
	char	character;

	if (pressed[KEY_1_L_CTRL] || pressed[KEY_1_R_CTRL])
		return;

	switch (scancode) {
		case KEY_1_ESC:
			setActive(false);
			VGA::hideCursor();
			return;

		case KEY_1_CURSOR_LEFT:
			if (_cmdCursor > 0) {
				_cmdCursor--;
				if (_cmdCursor > 0 && _cmd[_cmdCursor - 1] == '\xff')
					_cmdCursor--;
				refreshCommand();
			}
			return;

		case KEY_1_CURSOR_RIGHT:
			if (_cmdCursor < CMD_MAX_LEN - 1 && _cmd[_cmdCursor]) {
				if (_cmd[_cmdCursor] == '\xff')
					_cmdCursor++;
				_cmdCursor++;
				refreshCommand();
			}
			return;

		case KEY_1_CURSOR_UP:
			while (_cmdCursor > 0) {
				_cmdCursor--;
				if (_cmdCursor > 0 && _cmd[_cmdCursor - 1] == '\xff')
					_cmdCursor--;
			}
			refreshCommand();
			return;

		case KEY_1_CURSOR_DOWN:
			while (_cmdCursor < CMD_MAX_LEN - 1 && _cmd[_cmdCursor]) {
				if (_cmd[_cmdCursor] == '\xff')
					_cmdCursor++;
				_cmdCursor++;
			}
			refreshCommand();
			return;

		case KEY_1_BACKSPACE:
			if (_cmdCursor > 0) {
				string::removeSubstring(_cmd, _cmdCursor - 1, 1);
				_cmdCursor--;
				refreshCommand();
			}
			return;

		case KEY_1_DELETE:
			if (_cmdCursor < CMD_MAX_LEN - 1 && _cmd[_cmdCursor]) {
				string::removeSubstring(_cmd, _cmdCursor, 1);
				refreshCommand();
			}
			return;

		case KEY_1_ENTER:
		case KEY_1_KP_ENTER:
			putc('\n');
			_lastResult = executeCommand();
			resetCommand();
			scrollToCursor();
			updateVGACursor();
			return;
	}

	character = caps ? getUpperKey(scancode) : getLowerKey(scancode);
	if (!character)
		return;

	if ((pressed[KEY_1_L_ALT] || pressed[KEY_1_R_ALT])
			&& string::ishex(character)) {
		_altValue = (_altValue << 4) | string::gethexval(character);
		_altCount++;
		if (_altCount < 2)
			return;
		if (string::insert(_cmd, "\xff", _cmdCursor, 1, CMD_MAX_LEN - 1))
			return;
		_cmdCursor++;
		character = (char) _altValue;
	}
	if (_altCount != 0) {
		_altValue = 0x00;
		_altCount = 0;
	}
	if (string::insert(_cmd, &character, _cmdCursor, 1, CMD_MAX_LEN)) // TODO: Forbid when tab
		return;
	_cmdCursor++;
	refreshCommand();
}

void	CommandPrompt::eraseCommand() {
	while (_cmdRenderEnd > _cmdRenderStart) {
		if (_cmdRenderEnd.x == 0) {
			_cmdRenderEnd.x = _size.x - 1;
			_cmdRenderEnd.y--;
		} else
			_cmdRenderEnd.x--;
		_writec(_cmdRenderEnd.x, _cmdRenderEnd.y, _color);
	}
}

void	CommandPrompt::flushCommand() {
	_cur = _cmdRenderStart.clone();
	put(_cmd);
	_cmdRenderEnd = _cur.clone();
}

void	CommandPrompt::refreshCommand() {
	eraseCommand();
	flushCommand();
	scrollToCursor();
	updateVGACursor();
}

void	CommandPrompt::resetCommand() {
	for (size_t i = 0; i < CMD_MAX_LEN; i++)
		_cmd[i] = 0;
	_cmdCursor = 0;
	printk(CMD_PREFIX);
	_cmdRenderStart = _cur.clone();
	_cmdRenderEnd = _cur.clone();
}

void	CommandPrompt::updateVGACursor() {
	Vect2<size_t> pos =  _cmdRenderStart.clone();
	for (size_t i = 0; i < _cmdCursor && _cmd[i]; i++) {
		if (_cmd[i] == '\xff')
			i++;
		pos.x++;
		if (pos.x >= _size.x) {
			pos.x = 0;
			pos.y++;
		}
	}
	VGA::moveCursor(VGA::pos(pos.y + _renderPos.y - _scrollY, pos.x + _renderPos.x));
}

int	CommandPrompt::executeCommand() {
	return executeCommand(_cmd);
}

int	CommandPrompt::executeCommand(char *cmdLine) {
	size_t	argc = 0;
	char	argv[CMD_MAX_ARGS][CMD_MAX_LEN] = {{0}};
	char	*argvPtrs[CMD_MAX_ARGS] = {0};
	for (size_t i = 0; i < CMD_MAX_ARGS; i++)
		argvPtrs[i] = argv[i];

	string::split(cmdLine, ' ', argvPtrs, &argc, CMD_MAX_LEN, CMD_MAX_ARGS);
	if (!argv[0][0])
		return _lastResult;

	cmd_func_t func = getCommandFunc(argv[0]);
	if (!func) {
		printk("Unknown command: %s\n", argv[0]);
		return -1;
	}
	return func(this, cmdLine, argc, argvPtrs);
}
