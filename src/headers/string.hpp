/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:51:36 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/23 14:17:21 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_HPP
#define STRING_HPP

void	itoa(int32_t n, char buffer[12]);
void	lltox(int64_t n, char buffer[18], bool upper = false);
void	ulltox(uint64_t n, char buffer[17], bool upper = false);
size_t	strlen(const char *str);
bool	isalpha(char c);

#endif