/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:51:36 by bsavinel          #+#    #+#             */
/*   Updated: 2026/02/13 14:34:44 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_HPP
#define STRING_HPP

namespace string {
	int64_t	atoll(const char *str);
	void	itoa(int32_t n, char buffer[12]);
	void	lltox(int64_t n, char buffer[18], bool upper = false);
	void	ulltox(uint64_t n, char buffer[17], bool upper = false);
	size_t	strlen(const char *str);
	bool	isalpha(char c);
	bool	ishex(char c);
	bool	isDigit(char c);
	bool	isPrintable(char c);
	uint8_t	gethexval(char c);
	int		strcmp(const char *s1, const char *s2);
	void	*memset (void *s, int c, size_t n);
	void	*memcpy (void *dest, const void *src, size_t n);
	int		countDigitsInBase(int n, int base);
	int		countUDigitsInBase(uint32_t n, uint32_t base);

	
	long unsigned int	hexStringToInt(const char *str);
	size_t				atosize_t(const char *str);

	/**
	 * Splits a string into tokens based on a delimiter.
	 *
	 * @param str The string to split.
	 * @param delim The delimiter character.
	 * @param table A pointer to a char[][] to store the tokens. Must be pre-allocated with maxHeight rows and maxWidth columns.
	 * @param savelen A pointer to a size_t variable to store the number of tokens found.
	 * @param maxWidth The maximum width of each token (including null terminator).
	 * @param maxHeight The maximum number of tokens to split (including null terminator).
	 *
	 * @return A pointer to where the next token would start in the original string after the last split, or NULL if an error occurs.
	 */
	char	*split(char *str, char delim, char **table, size_t *savelen, size_t maxWidth, size_t maxHeight);

	/**
	 * @brief Inserts a substring into a string, shifting the existing characters to the right.
	 *
	 * @param dest The destination string where `src` will be inserted. Must be null-terminated and have enough space to hold the result.
	 * @param src The source string to insert. (Must be null-terminated if `amount` is `-1`)
	 * @param index The index in `dest` where `src` should be inserted. Must be less than or equal to the length of `dest`.
	 * @param amount The amount of characters to insert. `-1` to insert the entire `src` string.
	 * @param maxLen The maximum length of the destination string (including the null terminator).
	 *
	 * @return `0` on success, `-1` on failure.
	 */
	int		insert(char *dest, const char *src, size_t index, ssize_t amount, size_t maxLen);

	/**
	 * @brief Removes a substring from a string, shifting the remaining characters to the left.
	 *
	 * @param str The string to modify. Must be null-terminated.
	 * @param index The starting index of the substring to remove.
	 * @param length The length of the substring to remove.
	 *
	 * @return `0` on success, `-1` on failure.
	 */
	int		removeSubstring(char *str, size_t index, size_t length);
}

#endif