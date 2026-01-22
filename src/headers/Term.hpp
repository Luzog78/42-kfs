/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:22:57 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 08:33:58 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_HPP
#define TERM_HPP

#include "header.hpp"

#define TERM_PTR				((uint16_t *) VGA_MEMORY)
#define TERM_MAX_HIST_HEIGHT	(VGA_HEIGHT * 5)
#define TERM_DEFAULT_COLOR		VGA::character(VGA_C_LIGHT_GREY, VGA_C_BLACK)

class Term {
	private:
		/** Size of the terminal (`0 <= x < VGA_WIDTH` and `0 <= y < VGA_HEIGHT`). */
		Vect2<size_t>	_size;
		/** Height of the history buffer, containing active screen. */
		size_t			_histHeight;

		/** The current color of the cursor. */
		uint16_t		_color;
		/** Cursor position (`0 <= x < _size.x` and `0 <= y < _histHeight`). */
		Vect2<size_t>	_cur;

		/** From where on the VGA screen are we rendering (`0 <= x < VGA_WIDTH` and `0 <= y < VGA_HEIGHT`). */
		Vect2<size_t>	_renderPos;
		/** From which part of the terminal are we rendering (`∈ [0; _histHeight]`). */
		size_t			_scrollY;
		/** Updating the screen in addition to the buffer? */
		bool			_rendering;

		uint16_t		_buffer[VGA_WIDTH * TERM_MAX_HIST_HEIGHT];
		size_t			_bufferSize;

		void			_init();
		void			_writec(size_t x, size_t y, uint16_t vgaChar);
		void			_flushc(size_t x, size_t y);

	public:
		/**
		 * @brief Returns a writable character for the terminal.
		 *
		 * @param c The character to check. Supported range: `[0; 159]`.
		 * @param replace The character to return when not writable. Supported range: `[0; 159]`.
		 *
		 * @return uchar_t The writable char (range: `[1; 127]`), `0` if position char, or `replace` if not writable.
		 *
		 * @note Classic ASCII chars: `[0; 127]`.
		 * @note Classic ASCII printable chars: `[32; 126]`.
		 *
		 * ---
		 *
		 * @note There is extra 32 special chars: `[1; 31]` and `127`.
		 * @note If we put the special chars after the `127` default chars,
		 * @note  there is `160` supported chars, so the range of acceptable
		 * @note  characters is `[0; 159]` (`127 + 32`).
		 *
		 * ---
		 *
		 * @note Only from `32` to `126` and `128` to `159` are writable.
		 * @note If `c` is writable:
		 * @note   return `c == 128` ? `127` : `c >= 128` ? `c - 128` : `c`
		 */
		static uchar_t	getWritable(const uchar_t c, const uchar_t replace);

		Term();
		Term(const Term &other);
		Term(uint16_t vgaColor);
		Term(Vect2<size_t> size);
		Term(Vect2<size_t> size, uint16_t vgaColor);
		Term(Vect2<size_t> size, size_t histHeight);
		Term(Vect2<size_t> size, size_t histHeight, uint16_t vgaColor);
		Term(Vect2<size_t> size, Vect2<size_t> renderPos);
		Term(Vect2<size_t> size, Vect2<size_t> renderPos, uint16_t vgaColor);
		Term(Vect2<size_t> size, Vect2<size_t> renderConfm, size_t histHeight);
		Term(Vect2<size_t> size, Vect2<size_t> renderPos, size_t histHeight, uint16_t vgaColor);

		Term	&operator=(const Term &other);
		~Term();

		void	incr(const char c);
		void	shiftHistUp(size_t lines);

		void	putc(uint16_t vgaChar);
		void	putc(const char c);
		void	putc(const char c, uint16_t vgaColor);

		void	write(uint16_t *vgaStr, size_t len);
		void	write(const char *str, size_t len);
		void	write(const char *str, uint16_t vgaColor, size_t len);

		void	put(uint16_t *vgaStr);
		void	put(const char *str);
		void	put(const char *str, uint16_t vgaColor);

		void	putn(int nb);
		void	putn(int nb, uint16_t vgaColor);

		void	putnHex(unsigned int nb);
		void	putnHex(unsigned int nb, uint16_t vgaColor);

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
		size_t			scrollToCursor();
		void			resetScrollY();

		bool			isRendering() const;
		bool			setRendering(bool enable);

		void	printkSpecifier(const char *fmt, void **arg);
		void	printk(const char *fmt, ...);

};

#endif
