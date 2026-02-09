/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:22:57 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/08 17:06:45 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_HPP
#define TERM_HPP

#include "header.hpp"

#define TERM_PTR				((uint16_t *) VGA_MEMORY)
#define TERM_MAX_HIST_HEIGHT	(VGA_HEIGHT * 5)
#define TERM_DEFAULT_COLOR		VGA::character(VGA_C_LIGHT_GREY, VGA_C_BLACK)

class Term {
	protected:
		/** Size of the terminal (`0 <= x < VGA_WIDTH` and `0 <= y < VGA_HEIGHT`). */
		Vect2<size_t>	_size;
		/** Height of the history buffer, containing active screen. */
		size_t			_histHeight;

		/** The current color of the cursor. */
		uint16_t		_color;
		/** Cursor position (`0 <= x < _size.x` and `0 <= y < _histHeight`). */
		Vect2<size_t>	_cur;
		/** If the next character is a special character. */
		bool			_alt;

		/** Used to store parts of the future alt character. */
		uint8_t			_altValue = 0x00;
		/** Count how many parts the future alt character has (1 part = 4 bits). */
		uint8_t			_altCount = 0;

		/** From where on the VGA screen are we rendering (`0 <= x < VGA_WIDTH` and `0 <= y < VGA_HEIGHT`). */
		Vect2<size_t>	_renderPos;
		/** From which part of the terminal are we rendering (`∈ [0; _histHeight]`). */
		size_t			_scrollY;
		/** Updating the screen in addition to the buffer? */
		bool			_rendering;
		/** Is the terminal active? If so, it will move the VGA cursor. */
		bool			_active;
		/** Used for put and write optimization. */
		bool			_tmpActive;

		uint16_t		_buffer[VGA_WIDTH * TERM_MAX_HIST_HEIGHT];
		size_t			_bufferSize;

		void			_init();
		void			_writec(size_t x, size_t y, uint16_t vgaChar);
		void			_flushc(size_t x, size_t y);
		void			_printkSpecifier(const char *fmt, void **arg);

	public:
		/**
		 * @brief Returns a writable character for the terminal.
		 *
		 * @param c The character to check.
		 * @param replace The character to return when not writable.
		 *
		 * @return char The writable char (range: `[1; 127]`), `0` if position char, or `replace` if not writable.
		 */
		static char	getWritable(const char c, const char replace);

		Term();
		Term(const Term &other);
		Term(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor);
		Term(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor, size_t histHeight);

		Term	&operator=(const Term &other);
		~Term();

		virtual void	onKeyDown(uint16_t scancode, bool *pressed, bool caps);

		void	incr(const char c, bool applyWhiteSpaces, bool applyControl = true);
		void	shiftHistUp(size_t lines);

		void	putc(uint16_t vgaChar, bool applyWhiteSpaces = true);
		void	putc(const char c, bool applyWhiteSpaces = true);
		void	putc(const char c, uint16_t vgaColor, bool applyWhiteSpaces = true);

		void	write(uint16_t *vgaStr, size_t len);
		void	write(const char *str, size_t len);
		void	write(const char *str, uint16_t vgaColor, size_t len);

		void	put(uint16_t *vgaStr);
		void	put(const char *str);
		void	put(const char *str, uint16_t vgaColor);

		void	putn(int nb);
		void	putn(int nb, uint16_t vgaColor);

		void	putHex(int64_t nb, bool caps = false);
		void	putHex(int64_t nb, bool caps, uint16_t vgaColor);
		void	putUHex(uint64_t nb, bool caps = false);
		void	putUHex(uint64_t nb, bool caps, uint16_t vgaColor);

		void	printk(const char *fmt, ...);

		void	fill(uint16_t vgaChar);
		void	fill(const char c);

		void	clear();
		void	flush();

		Vect2<size_t>	getSize() const;
		void			setSize(Vect2<size_t> size);

		size_t			getHistHeight() const;
		void			setHistHeight(size_t height);

		uint16_t		getColor() const;
		void			setColor(uint16_t color);

		Vect2<size_t>	getCursor() const;
		void			setCursor(Vect2<size_t> pos);
		void			moveCursor(int dx, int dy);
		void			resetCursor();

		Vect2<size_t>	getRenderPos() const;
		void			setRenderPos(Vect2<size_t> renderPos);

		size_t			getScrollY() const;
		void			setScrollY(size_t scrollY);
		size_t			incrScrollY(ssize_t delta);
		size_t			scrollToCursor(bool flushIfNeeded = true);
		void			resetScrollY();

		bool			isRendering() const;
		void			setRendering(bool enable);
		bool			isActive() const;
		void			setActive(bool enable);
		void			updateVGACursor();
};

#endif
