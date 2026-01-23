/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:37 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/23 13:16:36 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Term::Term() :
		_size(VGA_WIDTH, VGA_HEIGHT),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(TERM_DEFAULT_COLOR),
		_renderPos(0, 0) {
	_init();
}

Term::Term(uint16_t vgaColor) :
		_size(VGA_WIDTH, VGA_HEIGHT),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(vgaColor),
		_renderPos(0, 0) {
	_init();
}

Term::Term(Vect2<size_t> size) :
		_size(size.clone()),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(TERM_DEFAULT_COLOR),
		_renderPos(0, 0) {
	_init();
}

Term::Term(Vect2<size_t> size, uint16_t vgaColor) :
		_size(size.clone()),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(vgaColor),
		_renderPos(0, 0) {
	_init();
}

Term::Term(Vect2<size_t> size, size_t histHeight) :
		_size(size.clone()),
		_histHeight(histHeight),
		_color(TERM_DEFAULT_COLOR),
		_renderPos(0, 0) {
	_init();
}

Term::Term(Vect2<size_t> size, size_t histHeight, uint16_t vgaColor) :
		_size(size.clone()),
		_histHeight(histHeight),
		_color(vgaColor),
		_renderPos(0, 0) {
	_init();
}

Term::Term(Vect2<size_t> size, Vect2<size_t> renderPos) :
		_size(size.clone()),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(TERM_DEFAULT_COLOR),
		_renderPos(renderPos.clone()) {
	_init();
}

Term::Term(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor) :
		_size(size.clone()),
		_histHeight(TERM_MAX_HIST_HEIGHT),
		_color(vgaColor),
		_renderPos(renderPos.clone()) {
	_init();
}

Term::Term(Vect2<size_t> size, Vect2<size_t> renderPos, size_t histHeight) :
		_size(size.clone()),
		_histHeight(histHeight),
		_color(TERM_DEFAULT_COLOR),
		_renderPos(renderPos.clone()) {
	_init();
}

Term::Term(Vect2<size_t> size, Vect2<size_t> renderPos, size_t histHeight, uint16_t vgaColor) :
		_size(size.clone()),
		_histHeight(histHeight),
		_color(vgaColor),
		_renderPos(renderPos.clone()) {
	_init();
}

Term::Term(const Term &other) : Term(
	other._size,
	other._renderPos,
	other._histHeight,
	other._color
) {
	_cur = other._cur;
}

Term	&Term::operator=(const Term &other) {
	if (this != &other) {
		_size = other._size;
		_histHeight = other._histHeight;

		_color = other._color;
		_cur = other._cur;

		_renderPos = other._renderPos;
		_scrollY = other._scrollY;
		_rendering = other._rendering;

		for (size_t i = 0; i < other._bufferSize; i++)
			_buffer[i] = other._buffer[i];
		_bufferSize = other._bufferSize;
	}
	return *this;
}

Term::~Term() {}


/* ************************************************************************** */


void	Term::_init() {
	_size.x = Math::clamp<size_t>(_size.x, 1, VGA_WIDTH);
	_size.y = Math::clamp<size_t>(_size.y, 1, VGA_HEIGHT);
	_histHeight = Math::clamp<size_t>(_histHeight, 1, TERM_MAX_HIST_HEIGHT);

	_cur.x = Math::clamp<size_t>(_cur.x, 0, _size.x - 1);
	_cur.y = Math::clamp<size_t>(_cur.y, 0, _size.y - 1);

	_scrollY = Math::clamp<ssize_t>(_cur.y - _size.y - 1, 0, _histHeight);
	_rendering = true;
	_active = false;

	_bufferSize = VGA_WIDTH * _histHeight;

	stack_check(true);

	if (_color) {
		bool rendering = _rendering;
		_rendering = false;
		fill(_color);
		_rendering = rendering;
	}
}

void	Term::_writec(size_t x, size_t y, uint16_t vgaChar) {
	_buffer[VGA::pos(y, x)] = vgaChar;

	if (_rendering) {
		Vect2<ssize_t>	loc = Vect2<ssize_t>(x, y - _scrollY);
		if (loc.x < 0 || loc.x >= (ssize_t) _size.x
				|| loc.y < 0 || loc.y >= (ssize_t) _size.y)
			return;
		ssize_t	pos = VGA::pos(loc.y + _renderPos.y, loc.x + _renderPos.x);
		if (pos < VGA_SIZE) // pos >= 0 always true since loc.x and loc.y are >= 0
			TERM_PTR[pos] = vgaChar;
	}
}

void	Term::_flushc(size_t x, size_t y) {
	Vect2<ssize_t>	loc = Vect2<ssize_t>(x, y - _scrollY);
	if (loc.x < 0 || loc.x >= (ssize_t) _size.x
			|| loc.y < 0 || loc.y >= (ssize_t) _size.y)
		return;
	ssize_t	pos = VGA::pos(loc.y + _renderPos.y, loc.x + _renderPos.x);
	if (pos >= 0 && pos < VGA_SIZE)
		TERM_PTR[pos] = _buffer[VGA::pos(y, x)];
}

void	Term::incr(const char c, bool applyWhiteSpaces) {
	switch (c) {
		case '\n':
			if (applyWhiteSpaces)
				while (_cur.x < _size.x)
					_writec(_cur.x++, _cur.y, _color);
			_cur.x = 0;
			_cur.y++;
			break;

		case '\r':
			if (_cur.x <= 0) {
				_cur.y--;
				if (applyWhiteSpaces)
					for (size_t x = 0; x < _size.x; x++)
						_writec(x, _cur.y, _color);
			} else if (applyWhiteSpaces)
				for (size_t x = 0; x < _cur.x; x++)
					_writec(x, _cur.y, _color);
			_cur.x = 0;
			break;

		case '\t':
			if (applyWhiteSpaces) {
				size_t	toWrite = 4 - (_cur.x % 4);
				for (size_t i = 0; i < toWrite; i++)
					_writec(_cur.x++, _cur.y, _color);
				break;
			}
			_cur.x += 4 - (_cur.x % 4);
			break;

		case '\b':
			if (_cur.x <= 0) {
				_cur.y--;
				_cur.x = _size.x;
			}
			_cur.x--;
			if (applyWhiteSpaces)
				_writec(_cur.x, _cur.y, _color);
			break;

		default:
			_cur.x++;
			break;
	}

	if (_cur.x >= _size.x) {
		_cur.x = 0;
		_cur.y++;
	}
	if (_cur.y >= _histHeight) {
		_cur.y = _histHeight - 1;
		shiftHistUp(1);
	}
}

void	Term::shiftHistUp(size_t lines) {
	for (size_t y = lines; y < _histHeight; y++)
		for (size_t x = 0; x < _size.x; x++)
			_writec(x, y - lines, _buffer[VGA::pos(y, x)]);
	for (size_t x = 0; x < _size.x; x++)
		_writec(x, _histHeight - 1, _color);
}

void	Term::putc(uint16_t vgaChar, bool applyWhiteSpaces) {
	putc(VGA::getChar(vgaChar), VGA::getColor(vgaChar), applyWhiteSpaces);
}

void	Term::putc(const char c, bool applyWhiteSpaces) {
	uchar_t	w = getWritable(c, 132);
	if (w)
		_writec(_cur.x, _cur.y, w | _color);
	incr(c, applyWhiteSpaces);
	if (_active)
		updateVGACursor();
}

void	Term::putc(const char c, uint16_t vgaColor, bool applyWhiteSpaces) {
	uchar_t	w = getWritable(c, 132);
	if (w)
		_writec(_cur.x, _cur.y, w | vgaColor);
	incr(c, applyWhiteSpaces);
	if (_active)
		updateVGACursor();
}

void Term::putn(int nb) {
	char	buffer[7];

	itoa(nb, buffer);
	put(buffer);
}

void Term::putn(int nb, uint16_t vgaColor) {
	char	buffer[7];

	itoa(nb, buffer);
	put(buffer, vgaColor);
}

void Term::putHex(int64_t nb, bool caps) {
	char buffer[18];

	lltox(nb, buffer, caps);
	put(buffer);
}

void Term::putHex(int64_t nb, bool caps, uint16_t vgaColor) {
	char buffer[18];

	lltox(nb, buffer, caps);
	put(buffer, vgaColor);
}

void Term::putUHex(uint64_t nb, bool caps) {
	char buffer[18];

	ulltox(nb, buffer, caps);
	put(buffer);
}

void Term::putUHex(uint64_t nb, bool caps, uint16_t vgaColor) {
	char buffer[18];

	ulltox(nb, buffer, caps);
	put(buffer, vgaColor);
}

void Term::write(const char *str, size_t len) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; i < len; i++)
		putc(str[i]);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::write(uint16_t *vgaStr, size_t len) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; i < len; i++)
		putc(vgaStr[i]);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::write(const char *str, uint16_t vgaColor, size_t len) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; i < len; i++)
		putc(str[i], vgaColor);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::put(const char *str) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; str[i]; i++)
		putc(str[i]);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::put(uint16_t *vgaStr) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; vgaStr[i]; i++)
		putc(vgaStr[i]);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::put(const char *str, uint16_t vgaColor) {
	_tmpActive = _active, _active = false;
	for (size_t i = 0; str[i]; i++)
		putc(str[i], vgaColor);
	if ((_active = _tmpActive))
		updateVGACursor();
}

void	Term::fill(uint16_t vgaChar) {
	for (size_t y = 0; y < _histHeight; y++)
		for (size_t x = 0; x < _size.x; x++)
			_writec(x, y, vgaChar);
}

void	Term::fill(const char c) {
	for (size_t y = 0; y < _histHeight; y++)
		for (size_t x = 0; x < _size.x; x++)
			_writec(x, y, c | _color);
}

void	Term::clear() {
	fill(_color);
}

void	Term::flush() {
	size_t maxY = Math::min<size_t>(_histHeight, _size.y + _scrollY);
	for (size_t y = _scrollY; y < maxY; y++)
		for (size_t x = 0; x < _size.x; x++)
			_flushc(x, y);
}

/* ************************************************************************** */


Vect2<size_t>	Term::getSize() const {
	return _size.clone();
}

void	Term::setSize(Vect2<size_t> size) {
	_size.x = Math::clamp<size_t>(size.x, 1, VGA_WIDTH);
	_size.y = Math::clamp<size_t>(size.y, 1, VGA_HEIGHT);
}

size_t	Term::getHistHeight() const {
	return _histHeight;
}

void	Term::setHistHeight(size_t height) {
	_histHeight = Math::clamp<size_t>(height, 1, TERM_MAX_HIST_HEIGHT);
}

uint16_t	Term::getColor() const {
	return _color;
}

void	Term::setColor(uint16_t color) {
	_color = color;
}

Vect2<size_t>	Term::getCursor() const {
	return _cur.clone();
}

void	Term::setCursor(Vect2<size_t> pos) {
	_cur.x = Math::clamp<size_t>(pos.x, 0, _size.x - 1);
	_cur.y = Math::clamp<size_t>(pos.y, 0, _size.y - 1);
}

void	Term::moveCursor(int dx, int dy) {
	setCursor(Vect2<size_t>(
		Math::clamp<ssize_t>(_cur.x + dx, 0, _size.x - 1),
		Math::clamp<ssize_t>(_cur.y + dy, 0, _size.y - 1)
	));
}

void	Term::resetCursor() {
	_cur.x = 0;
	_cur.y = 0;
}

Vect2<size_t>	Term::getRenderPos() const {
	return _renderPos.clone();
}

void	Term::setRenderPos(Vect2<size_t> renderPos) {
	_renderPos.x = Math::clamp<size_t>(renderPos.x, 0, VGA_WIDTH);
	_renderPos.y = Math::clamp<size_t>(renderPos.y, 0, VGA_HEIGHT);
}

size_t	Term::getScrollY() const {
	return _scrollY;
}

void	Term::setScrollY(size_t scrollY) {
	_scrollY = Math::clamp<size_t>(scrollY, 0, _histHeight - _size.y);
}

size_t	Term::incrScrollY(ssize_t delta) {
	setScrollY(_scrollY + delta);
	return _scrollY;
}

size_t	Term::scrollToCursor(bool flushIfNeeded) {
	if (_cur.y < _scrollY) {
		_scrollY = _cur.y;
		if (flushIfNeeded)
			flush();
	} else if (_cur.y >= _scrollY + _size.y) {
		_scrollY = _cur.y - _size.y + 1;
		if (flushIfNeeded)
			flush();
	}
	return _scrollY;
}

void	Term::resetScrollY() {
	_scrollY = 0;
}

bool	Term::isRendering() const {
	return _rendering;
}

void	Term::setRendering(bool enable) {
	_rendering = enable;
}

bool	Term::isActive() const {
	return _active;
}

void	Term::setActive(bool enable) {
	_active = enable;
	if (enable)
		updateVGACursor();
}

void	Term::updateVGACursor() {
	ssize_t	x = Math::clamp<ssize_t>(_cur.x, 0, _size.x - 1);
	ssize_t	y = Math::clamp<ssize_t>(_cur.y - _scrollY, 0, _size.y - 1);

	VGA::moveCursor(y + _renderPos.y, x + _renderPos.x);
}


/* ************************************************************************** */


uchar_t	Term::getWritable(const uchar_t c, const uchar_t replace) {
	if (c == '\n' || c == '\r' || c == '\t' || c == '\b')
		return 0; // Position char
	if (c < 32 || c >= 160 || c == 127)
		return replace; // Not writable
	if (c == 128)
		return 127; // Special char
	if (c > 128)
		return c - 128; // Special chars in range: [1; 31]
	return c; // Classic printable char
}

void Term::printkSpecifier(const char *fmt, void **arg) {
	switch (*fmt) {
		case 'c':
			putc(*(char *) arg);
			break;
		case 's':
			put(*(const char **) arg);
			break;
		case 'p':
			put("0x");
			putUHex(*(uint64_t *) arg, false);
			break;
		case 'd':
		case 'i':
			putn(*(int *) arg);
			break;
		case 'u':
			putn(*(unsigned int *) arg);
			break;
		case 'x':
			putHex(*(int *) arg, false);
			break;
		case 'X':
			putHex(*(int *) arg, true);
			break;
		case '%':
			putc('%');
			break;
	}
}

void Term::printk(const char *fmt, ...) {
	int i = 0;
	void **spec = (void **)&fmt;
	spec++;

	while (fmt[i]) {
		if (fmt[i] == '%') {
			printkSpecifier(&fmt[i + 1], spec);
			i++;
			if (fmt[i] != '%')
				spec++;
		} else
			putc(fmt[i]);
		i++;
	}
}
