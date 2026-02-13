/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:31:32 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 13:51:46 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIMITS_HPP
#define LIMITS_HPP

#define INT8_MIN		-128
#define INT8_MAX		127
#define UINT8_MAX		255

#define INT16_MIN		-32768
#define INT16_MAX		32767
#define UINT16_MAX		65535

#define INT32_MIN		-2147483648
#define INT32_MAX		2147483647
#define UINT32_MAX		4294967295U

#define INT64_MIN		(-9223372036854775807LL - 1)
#define INT64_MAX		9223372036854775807LL
#define UINT64_MAX		18446744073709551615ULL


#define CHAR_MIN		INT8_MIN
#define CHAR_MAX		INT8_MAX
#define UCHAR_MAX		UINT8_MAX

#define SHORT_MIN		INT16_MIN
#define SHORT_MAX		INT16_MAX
#define USHORT_MAX		UINT16_MAX

#define INT_MIN			INT32_MIN
#define INT_MAX			INT32_MAX
#define UINT_MAX		UINT32_MAX

#define LLONG_MIN		INT64_MIN
#define LLONG_MAX		INT64_MAX
#define ULLONG_MAX		UINT64_MAX

#define SSIZE_MIN		INT64_MIN
#define SSIZE_MAX		INT64_MAX
#define SIZE_MAX		UINT64_MAX

#define ADDR_MAX		0x0000FFFF

#endif
