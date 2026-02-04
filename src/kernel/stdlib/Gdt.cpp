#include "Gdt.hpp"

Gdt::Gdt() : gdt_count(0) {
	memset(gdt_entries, 0, sizeof(gdt_entries));
}

Gdt::~Gdt() {
}

void Gdt::set_entry(uint64_t descriptor) {
	if (gdt_count < 6) {
		gdt_entries[gdt_count] = descriptor;
		gdt_count++;
	}
}

uint64_t Gdt::create_descriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

	return descriptor;
}

void Gdt::loadGDT() {
	uint32_t limit = (sizeof(uint64_t) * gdt_count) - 1;
	uint32_t base = (uint32_t)&gdt_entries;

	setGdt(limit, base);
}