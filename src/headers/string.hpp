/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:51:36 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/05 17:55:13 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_HPP
#define STRING_HPP

void	itoa(int32_t n, char buffer[12]);
void	lltox(int64_t n, char buffer[18], bool upper = false);
void	ulltox(uint64_t n, char buffer[17], bool upper = false);
size_t	strlen(const char *str);
bool	isalpha(char c);
bool	ishex(char c);
uint8_t	gethexval(char c);
void	*memset (void *s, int c, size_t n);
void	*memcpy (void *dest, const void *src, size_t n);
int		countDigitsInBase(int n, int base);
int		countUDigitsInBase(uint32_t n, uint32_t base);
bool	isDigit(char c);
bool	isPrintable(char c);

#endif