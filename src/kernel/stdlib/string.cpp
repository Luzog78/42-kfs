/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:33:01 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/13 13:20:59 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

namespace string {
	size_t	strlen(const char *str) {
		if (!str)
			return 0;

		size_t	len = 0;
		while (str[len])
			len++;
		return len;
	}

	int64_t	atoll(const char *str) {
		int64_t	result = 0;
		int		sign = 1;

		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		if (*str == '-') {
			sign = -1;
			str++;
		} else if (*str == '+') {
			str++;
		}
		while (*str >= '0' && *str <= '9') {
			result = result * 10 + (*str - '0');
			str++;
		}
		if (*str)
			return INT64_MIN;
		return (result * sign);
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

	char	*split(char *str, char delim, char **table, size_t *savelen, size_t maxWidth, size_t maxHeight) {
		if (!str || !table || maxWidth == 0 || maxHeight == 0)
			return 0;

		size_t	row = 0;
		size_t	col = 0;
		size_t	i = 0;

		for (; str[i] == delim; i++)
			/* Skip delimiters */;
		for (; str[i] && row < maxHeight - 1; i++) {
			if (str[i] == delim) {
				for (; str[i + 1] == delim; i++)
					/* Skip delimiters */;
				table[row][col] = '\0'; // Null-terminate the current token
				row++;
				col = 0;
			} else if (col < maxWidth - 1) {
				table[row][col] = str[i];
				col++;
			}
		}
		table[row][col] = '\0'; // Null-terminate the last token
		table[row + 1] = 0; // Null-terminate the table

		*savelen = row + 1; // Number of tokens stored in the table
		return str + i;
	}

	int	strcmp(const char *s1, const char *s2) {
		size_t	i = 0;

		if (!s1 && !s2)
			return 0;
		if (!s1)
			return -s2[0];
		if (!s2)
			return s1[0];

		while (s1[i] && s2[i]) {
			if (s1[i] != s2[i])
				return (s1[i] - s2[i]);
			i++;
		}
		return (s1[i] - s2[i]);
	}

	int	insert(char *dest, const char *src, size_t index, ssize_t amount, size_t maxLen) {
		if (!dest || !src)
			return -1;

		size_t	destLen = strlen(dest);
		size_t	srcLen = amount == -1 ? strlen(src) : (size_t) amount;

		if (index > destLen || destLen + srcLen >= maxLen)
			return -1;

		for (size_t i = destLen; i >= index; i--) {
			dest[i + srcLen] = dest[i];
			if (i == 0)
				break;
		}
		for (size_t i = 0; i < srcLen; i++)
			dest[index + i] = src[i];
		return 0;
	}

	int	removeSubstring(char *str, size_t index, size_t length) {
		if (!str)
			return -1;

		size_t	len = strlen(str);
		if (index >= len)
			return -1;

		for (size_t i = index; i < len - length; i++)
			str[i] = str[i + length];
		str[len - length] = '\0';
		return 0;
	}
	
	void *memset (void *s, int c, size_t n) {
		for (size_t i = 0; i < n; i++) {
			((unsigned char *)s)[i] = (unsigned char)c;
		}
		return s;
	}
	
	void *memcpy (void *dest, const void *src, size_t n) {
		for (size_t i = 0; i < n; i++) {
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		}
		return dest;
	}
	
	int	countDigitsInBase(int n, int base) {
		int	count = 0;
		if (n <= 0)
		count++;
		while (n != 0) {
			n /= base;
			count++;
		}
		return count;
	}
	
	int	countUDigitsInBase(uint32_t n, uint32_t base) {
		int	count = 0;
		if (n == 0)
		return 1;
		while (n != 0) {
			n /= base;
			count++;
		}
		return count;
	}
	
	bool	isDigit(char c) {
		return (c >= '0' && c <= '9');
	}
	
	bool	isPrintable(char c) {
		return (c >= 32 && c <= 126);
	}
}