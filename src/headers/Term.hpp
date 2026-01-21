/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:22:57 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/21 15:34:50 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_HPP
#define TERM_HPP

#include "header.hpp"

#define TERM_PTR	((uint16_t *) VGA_MEMORY)

class Term {
	private:
		Vect2<size_t>	_min = Vect2<size_t>(0, 0);
		Vect2<size_t>	_max = Vect2<size_t>(0, 0);
		Vect2<size_t>	_cur = Vect2<size_t>(0, 0);
		size_t			_pos = 0;
		uint16_t		_color = 0;

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
		Term(Vect2<size_t> min, Vect2<size_t> max);
		Term(size_t minX, size_t minY, size_t maxX, size_t maxY);
		Term(Vect2<size_t> min, Vect2<size_t> max, uint16_t vgaColor);
		Term(size_t minX, size_t minY, size_t maxX, size_t maxY, uint16_t vgaColor);

		Term	&operator=(const Term &other);
		~Term();

		void	incr(const char c);

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

		void	putn_hex(unsigned int nb);
		void	putn_hex(unsigned int nb, uint16_t vgaColor);

		void	fill(uint16_t vgaChar);
		void	fill(const char c);
		

		
		void	clear();
		
		Vect2<size_t>	getCursor() const;
		void			setCursor(Vect2<size_t> pos);
		void			resetCursor();
		
		Vect2<size_t>	getMin() const;
		void			setMin(Vect2<size_t> min);
		
		Vect2<size_t>	getMax() const;
		void			setMax(Vect2<size_t> max);
		
		uint16_t		getColor() const;
		void			setColor(uint16_t color);

		void	printk_specifier(const char *fmt, void **arg);
		void	printk(const char *fmt, ...);

};

#endif
