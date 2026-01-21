/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:37 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/21 17:11:21 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Term::Term() : Term(
	Vect2<size_t>(0, 0),
	Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT)
) {}

Term::Term(uint16_t vgaColor) : Term(
	Vect2<size_t>(0, 0),
	Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
	vgaColor
) {}

Term::Term(Vect2<size_t> min, Vect2<size_t> max) : Term(
	min.clone(),
	max.clone(),
	VGA::character(VGA_C_LIGHT_GREY, VGA_C_BLACK)
) {}

Term::Term(size_t minX, size_t minY, size_t maxX, size_t maxY) : Term(
	Vect2<size_t>(minX, minY),
	Vect2<size_t>(maxX, maxY)
) {}

Term::Term(Vect2<size_t> min, Vect2<size_t> max, uint16_t vgaColor) :
	_min(min.clone()),
	_max(max.clone()),
	_cur(Vect2<size_t>(min.x, min.y)),
	_pos(VGA::pos(min.y, min.x)),
	_color(vgaColor) {
}

Term::Term(size_t minX, size_t minY, size_t maxX, size_t maxY, uint16_t vgaColor) : Term(
	Vect2<size_t>(minX, minY),
	Vect2<size_t>(maxX, maxY),
	vgaColor
) {}

Term::Term(const Term &other) : Term(
	other._min,
	other._max,
	other._color
) {
	_cur = other._cur;
	_pos = other._pos;
}

Term	&Term::operator=(const Term &other) {
	if (this != &other) {
		_min = other._min;
		_max = other._max;
		_cur = other._cur;
		_pos = other._pos;
		_color = other._color;
	}
	return *this;
}

Term::~Term() {}


/* ************************************************************************** */


void	Term::incr(const char c) {
	switch (c) {
		case '\n':
			_cur.x = _min.x;
			_cur.y++;
			break;

		case '\r':
			if (_cur.x <= _min.x)
				_cur.y--;
			_cur.x = _min.x;
			break;

		case '\t':
			_cur.x += 4 - (_cur.x % 4);
			break;

		case '\b':
			if (_cur.x <= _min.x) {
				_cur.y--;
				_cur.x = _max.x;
			}
			_cur.x--;
			break;

		default:
			_cur.x++;
			break;
	}

	if (_cur.x >= _max.x) {
		_cur.x = _min.x;
		_cur.y++;
	}
	if (_cur.x < _min.x) {
		_cur.x = _max.x - 1;
		_cur.y--;
	}
	if (_cur.y >= _max.y)
		_cur.y = _min.y;
	if (_cur.y < _min.y)
		_cur.y = _max.y - 1;

	_pos = VGA::pos(_cur.y, _cur.x);
}

void	Term::putc(uint16_t vgaChar) {
	putc(VGA::get_char(vgaChar), VGA::get_color(vgaChar));
}

void	Term::putc(const char c) {
	uchar_t	w = getWritable(c, 132);
	if (w)
		TERM_PTR[_pos] = w | _color;
	incr(c);
}

void	Term::putc(const char c, uint16_t vgaColor) {
	uchar_t	w = getWritable(c, 132);
	if (w)
		TERM_PTR[_pos] = w | vgaColor;
	incr(c);
}

void Term::putn(int nb)
{
	put(itoa(nb));
}

void Term::putn(int nb, uint16_t vgaColor)
{
	put(itoa(nb), vgaColor);
}

void Term::putn_hex(unsigned int nb)
{
	char hex[] = "0123456789ABCDEF";
	static char str[11];
	int i = 9;

	str[10] = '\0';

	while (nb > 0 && i >= 0)
	{
		str[i] = hex[nb % 16];
		nb = nb / 16;
		i--;
	}
	str[i] = 'x';
	str[--i] = '0';
	put(&str[i]);
}

void Term::putn_hex(unsigned int nb, uint16_t vgaColor)
{
	char hex[] = "0123456789ABCDEF";
	static char str[11];
	int i = 9;

	str[10] = '\0';

	while (nb > 0 && i >= 0)
	{
		str[i] = hex[nb % 16];
		nb = nb / 16;
		i--;
	}
	put(&str[i + 1], vgaColor);
}

void Term::write(const char *str, size_t len)
{
	for (size_t i = 0; i < len; i++)
		putc(str[i]);
}

void	Term::write(uint16_t *vgaStr, size_t len) {
	for (size_t i = 0; i < len; i++)
		putc(vgaStr[i]);
}

void	Term::write(const char *str, uint16_t vgaColor, size_t len) {
	for (size_t i = 0; i < len; i++)
		putc(str[i], vgaColor);
}

void	Term::put(const char *str) {
	for (size_t i = 0; str[i]; i++)
		putc(str[i]);
}

void	Term::put(uint16_t *vgaStr) {
	for (size_t i = 0; vgaStr[i]; i++)
		putc(vgaStr[i]);
}

void	Term::put(const char *str, uint16_t vgaColor) {
	for (size_t i = 0; str[i]; i++)
		putc(str[i], vgaColor);
}

void	Term::fill(uint16_t vgaChar) {
	for (size_t y = _min.y; y < _max.y; y++)
		for (size_t x = _min.x; x < _max.x; x++)
			TERM_PTR[VGA::pos(y, x)] = vgaChar;
}

void	Term::fill(const char c) {
	for (size_t y = _min.y; y < _max.y; y++)
		for (size_t x = _min.x; x < _max.x; x++)
			TERM_PTR[VGA::pos(y, x)] = c | _color;
}

void	Term::clear() {
	fill(' ');
}

Vect2<size_t>	Term::getCursor() const {
	return _cur.clone();
}

void	Term::setCursor(Vect2<size_t> pos) {
	_cur = pos;
	_pos = VGA::pos(_cur.y, _cur.x);
}

void	Term::resetCursor() {
	_cur = Vect2<size_t>(_min.x, _min.y);
	_pos = VGA::pos(_cur.y, _cur.x);
}

Vect2<size_t>	Term::getMin() const {
	return _min.clone();
}

void	Term::setMin(Vect2<size_t> min) {
	_min = min;
}

Vect2<size_t>	Term::getMax() const {
	return _max.clone();
}

void	Term::setMax(Vect2<size_t> max) {
	_max = max;
}

uint16_t	Term::getColor() const {
	return _color;
}

void	Term::setColor(uint16_t color) {
	_color = color;
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


void Term::printk_specifier(const char *fmt, void **arg)
{
	switch (*fmt)
	{
	case 'c':
		putc((char)*(char *)(arg));
		break;
	case 's':
		put((const char *)*arg);
		break;
	case 'p':
		put("0x");
		putn_hex((unsigned int)arg);
		break;
	case 'd':
	case 'i':
		putn(*(int *)arg);
		break;
	case 'u':
		putn(*(unsigned int *)*arg);
		break;
	case 'x':
		putn_hex(*(unsigned int *)*arg);
		break;
	case '%':
		putc('%');
		break;
	}
}

void Term::printk(const char *fmt, ...)
{
	int i = 0;
	void **spec = (void **)&fmt;
	spec++;

	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			printk_specifier(&fmt[i + 1], spec);
			i++;
			if (fmt[i] != '%')
				spec++;
		}
		else
			putc(fmt[i]);
		i++;
	}
}