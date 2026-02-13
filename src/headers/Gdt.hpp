/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gdt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:50:47 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 17:27:50 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_HPP
#define GDT_HPP

#include "header.hpp"

/** Descriptor type: `0` -> system, `1` -> code/data */
#define SEG_DESCTYPE(x)		((x) << 0x04)
/** Present */
#define SEG_PRES(x)			((x) << 0x07)
/** Available for system use */
#define SEG_SAVL(x)			((x) << 0x0C)
/** Long mode */
#define SEG_LONG(x)			((x) << 0x0D)
/** Size: `0` -> 16-bit, `1` -> 32-bit */
#define SEG_SIZE(x)			((x) << 0x0E)
/** Granularity: `0` -> 1B - 1MB, `1` -> 4KB - 4GB */
#define SEG_GRAN(x)			((x) << 0x0F)
/** Privilege level (from `0` to `3`) */
#define SEG_PRIV(x)			(((x) & 0x03) << 0x05)

/** Read-Only */
#define SEG_DATA_RD			0x00
/** Read-Only, accessed */
#define SEG_DATA_RDA		0x01
/** Read/Write */
#define SEG_DATA_RDWR		0x02
/** Read/Write, accessed */
#define SEG_DATA_RDWRA		0x03
/** Read-Only, expand-down */
#define SEG_DATA_RDEXPD		0x04
/** Read-Only, expand-down, accessed */
#define SEG_DATA_RDEXPDA	0x05
/** Read/Write, expand-down */
#define SEG_DATA_RDWREXPD	0x06
/** Read/Write, expand-down, accessed */
#define SEG_DATA_RDWREXPDA	0x07
/** Execute-Only */
#define SEG_CODE_EX			0x08
/** Execute-Only, accessed */
#define SEG_CODE_EXA		0x09
/** Execute/Read */
#define SEG_CODE_EXRD		0x0A
/** Execute/Read, accessed */
#define SEG_CODE_EXRDA		0x0B
/** Execute-Only, conforming */
#define SEG_CODE_EXC		0x0C
/** Execute-Only, conforming, accessed */
#define SEG_CODE_EXCA		0x0D
/** Execute/Read, conforming */
#define SEG_CODE_EXRDC		0x0E
/** Execute/Read, conforming, accessed */
#define SEG_CODE_EXRDCA		0x0F

#define GDT_CODE_PL0		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(0)		| SEG_CODE_EXRDA

#define GDT_DATA_PL0		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(0)		| SEG_DATA_RDWRA

#define GDT_STACK_PL0		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(0)		| SEG_DATA_RDWREXPDA

#define GDT_CODE_PL3		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(3)		| SEG_CODE_EXRDA

#define GDT_DATA_PL3		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(3)		| SEG_DATA_RDWRA

#define GDT_STACK_PL3		SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0)	| \
							SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1)	| \
							SEG_PRIV(3)		| SEG_DATA_RDWREXPDA

extern uint64_t	gdt_entries_memory[7] __attribute__((section(".mygdt")));

/**
 * Global Descriptor Table (GDT) class.
 *
 * @see https://wiki.osdev.org/Global_Descriptor_Table
 * @see https://wiki.osdev.org/GDT_Tutorial
 */
class Gdt {
	private:
		uint64_t	_entries[7];
		int			_count;

	public:
		Gdt();
		~Gdt();

		static uint64_t	createDescriptor(uint32_t base, uint32_t limit, uint16_t flag);

		const uint64_t	*getEntries() const;
		void			setEntry(uint64_t descriptor);
		void			loadGDT();
};

#endif
