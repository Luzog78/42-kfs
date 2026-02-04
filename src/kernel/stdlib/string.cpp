/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:33:01 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/03 17:11:38 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

size_t	strlen(const char *str) {
	size_t	len = 0;
	while (str[len])
		len++;
	return len;
}

static int	numberLen(int n) {
	int	len;

	len = 0;
	if (n >= 0 && n < 10)
		return 1;
	if (n < 0 && n > -10)
		return 2;
	if (n < 0) {
		len++;
		n = -n;
	}
	while (n > 0) {
		n = n / 10;
		len ++;
	}
	return len;
}

void	itoa(int32_t n, char buffer[12]) {
	if (n == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}
	if (n == INT32_MIN) {
		buffer[0] = '-', buffer[1] = '2', buffer[2] = '1', buffer[3] = '4',
		buffer[4] = '7', buffer[5] = '4', buffer[6] = '8', buffer[7] = '3',
		buffer[8] = '6', buffer[9] = '4', buffer[10] = '8', buffer[11] = '\0';
		return;
	}

	int	i = numberLen(n) - 1;

	if (n < 0) {
		n = -n;
		buffer[0] = '-';
	}
	buffer[i + 1] = '\0';
	while (n > 0) {
		buffer[i] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
}

void	lltox(int64_t n, char buffer[18], bool upper) {
	if (n == INT64_MIN) {
		buffer[0] = '-', buffer[1] = '8', buffer[2] = '0', buffer[3] = '0',
		buffer[4] = '0', buffer[5] = '0', buffer[6] = '0', buffer[7] = '0',
		buffer[8] = '0', buffer[9] = '0', buffer[10] = '0', buffer[11] = '0',
		buffer[12] = '0', buffer[13] = '0', buffer[14] = '0', buffer[15] = '0',
		buffer[16] = '0', buffer[17] = '\0';
		return;
	}
	if (n < 0) {
		n = -n;
		buffer[0] = '-';
		ulltox(n, &buffer[1], upper);
		return;
	}
	ulltox(n, buffer, upper);
}

void	ulltox(uint64_t n, char buffer[17], bool upper) {
	const char	*base = upper ? "0123456789ABCDEF" : "0123456789abcdef";

	if (n == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}

	int	shift = 60;
	int	i = 0;

	while (shift >= 0) {
		uint8_t	val = (n >> shift) & 0xF;
		if (val != 0 || i > 0) {
			buffer[i] = base[val];
			i++;
		}
		shift -= 4;
	}
	buffer[i] = '\0';
}

bool isalpha(char c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool ishex(char c) {
	return ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
}

uint8_t gethexval(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	if (c >= 'a' && c <= 'f')
		return 10 + (c - 'a');
	return 0;
}

void *memset (void *s, int c, size_t n) {
	for (size_t i = 0; i < n; i++) {
		((unsigned char *)s)[i] = (unsigned char)c;
	}
	return s;
}