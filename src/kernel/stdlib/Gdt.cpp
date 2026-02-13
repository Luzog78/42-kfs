/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gdt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:56:23 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 17:21:59 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Gdt.hpp"

uint64_t	gdt_entries_memory[7] __attribute__((section(".mygdt")));

Gdt::Gdt() : _count(0) {
	string::memset(_entries, 0, sizeof(_entries));
}

Gdt::~Gdt() {
}


/* ************************************************************************** */


uint64_t Gdt::createDescriptor(uint32_t base, uint32_t limit, uint16_t flag) {
	uint64_t descriptor;
 
	// Create the high 32 bit segment
	descriptor  =  limit		& 0x000F0000; // set limit bits 19:16
	descriptor |= (flag <<  8)	& 0x00F0FF00; // set type, p, dpl, s, g, d/b, l and avl fields
	descriptor |= (base >> 16)	& 0x000000FF; // set base bits 23:16
	descriptor |=  base			& 0xFF000000; // set base bits 31:24
 
	// Shift by 32 to allow for low part of segment
	descriptor <<= 32;

	// Create the low 32 bit segment
	descriptor |= base << 16;			// set base bits 15:0
	descriptor |= limit & 0x0000FFFF;	// set limit bits 15:0

	return descriptor;
}

const uint64_t* Gdt::getEntries() const {
	return _entries;
}

void Gdt::setEntry(uint64_t descriptor) {
	if (_count < 7) {
		_entries[_count] = descriptor;
		_count++;
	}
}

void Gdt::loadGDT() {
	uint32_t limit = (sizeof(uint64_t) * _count) - 1;

	string::memcpy(gdt_entries_memory, _entries, sizeof(uint64_t) * _count);
	gdt_set_location(limit, (uint32_t)&gdt_entries_memory);
	gdt_reload_segments();
}
