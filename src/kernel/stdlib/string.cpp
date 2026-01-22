/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:33:01 by bsavinel          #+#    #+#             */
/*   Updated: 2026/01/22 16:46:42 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

size_t strlen(const char *str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static int	numberLen(int n) {
	int	len;

	len = 0;
	if (n >= 0 && n < 10)
		return (1);
	if (n < 0 && n > -10)
		return (2);
	if (n < 0) {
		len++;
		n = -n;
	}
	while (n > 0) {
		n = n / 10;
		len ++;
	}
	return (len);
}

char	*itoa(int n) {
	static char	str[7];
	int			i = numberLen(n) - 1;

	if (n == 0) {
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0) {
		n = -n;
		str[0] = '-';
	}
	str[i + 1] = '\0';
	while (n > 0) {
		str[i] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

bool isalpha(char c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
