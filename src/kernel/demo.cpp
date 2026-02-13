/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 23:17:49 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 13:30:40 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int		__DEMO_NO__ = DEMO_NO;
bool	__DEMO_RUN__ = false;

namespace Demo {
	int	(*demo(int no))() {
		switch (no) {
			case 1: return demo1;
			case 2: return demo2;
			case 3: return demo3;
			case 4: return demo4;
			default: return demoErr;
		}
	}

	int	demoErr() {
		Term term = Term(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_WHITE, VGA_C_LIGHT_RED)
		);

		term.put("Demo not found!\n");
		term.flush();
		for (uint64_t i = 0; i < 5000ull; i++)
			for (uint64_t j = 0; j < 1000000ull; j++)
				asm volatile ("nop");
		__DEMO_NO__ = 1;
		return 1;
	}

	int	demo1() {
		CommandPrompt	term0 = CommandPrompt(
			Vect2<size_t>(VGA_WIDTH, 17),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY)
		);
		Term			term1 = Term(
			Vect2<size_t>(23, 8),
			Vect2<size_t>(0, 17),
			VGA::character(VGA_C_DARK_GREY, VGA_C_BLACK)
		);
		Term			term2 = Term(
			Vect2<size_t>(32, 8),
			Vect2<size_t>(24, 17),
			VGA::character(VGA_C_LIGHT_GREY, VGA_C_BLACK)
		);
		Term			term3 = Term(
			Vect2<size_t>(23, 8),
			Vect2<size_t>(57, 17),
			VGA::character(VGA_C_WHITE, VGA_C_LIGHT_GREY)
		);
		Term			term4 = Term(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_GREEN, VGA_C_BLACK)
		);

		Term *terms[] = { &term0, &term1, &term2, &term3, &term4 };
		int activeTerm = 3;
		int shortcut = SHORTCUT_NONE;

		for (size_t line = 0; __42__[line]; line++)
			term0.put(__42__[line]);
		term0.put("\n");

		term0.put("You can switch between terminals with Ctrl+[1-5]!\n");
		term0.put("Type Alt+[0-f] Alt+[0-f] to write special characters using the CP437 ISO.\n\n", VGA::character(VGA_C_RED, VGA_C_CYAN));
		term0.resetCommand();

		for (int i = 0; i <= UCHAR_MAX; i++) {
			term1.printk("%x ", i);
			term1.scrollToCursor();
		}

		for (uint16_t i = 0; i < 256; i++) {
			term2.putc('\xff');
			term2.putc((char) i);
			term2.scrollToCursor();
		}

		term3.put("*You can type here...*\n");
		term3.put("*Ctrl+5 for more space*\n");

		term4.put("\xff\xd5\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd", VGA::character(VGA_C_BLUE));
		term4.put(" Welcome to the big terminal! ", VGA::character(VGA_C_BLACK, VGA_C_BLUE));
		term4.put("\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xb8", VGA::character(VGA_C_BLUE));
		term4.setCursor(Vect2<size_t>(0, 1));
		term4.put("\xff\xb3", VGA::character(VGA_C_BLUE));
		term4.setCursor(Vect2<size_t>(79, 1));
		term4.put("\xff\xb3", VGA::character(VGA_C_BLUE));
		term4.setCursor(Vect2<size_t>(2, 1));
		term4.put("*There is way more space here to tell the tale...*");
		term4.setCursor(Vect2<size_t>(0, 3));

		term0.flush();
		term1.flush();
		term2.flush();
		term3.flush();

		stack_check(true);
		terms[activeTerm]->setActive(true);
		while (__DEMO_RUN__) {
			if (activeTerm >= 0 && !terms[activeTerm]->isActive())
				activeTerm = -1;
			shortcut = handleKeyboard(activeTerm >= 0 ? terms[activeTerm] : nullptr);
			if (shortcut != SHORTCUT_NONE) {
				if (shortcut & FLAG_TERM_SWITCH && (shortcut & ~FLAG_TERM_SWITCH) < 5) {
					if (activeTerm >= 0)
						terms[activeTerm]->setActive(false);
					activeTerm = (shortcut & ~FLAG_TERM_SWITCH);
					terms[activeTerm]->setActive(true);
					terms[activeTerm]->flush();
					VGA::showCursor();
				}
			}
		}
		return 0;
	}

	int	demo2() {
		Term term = Term(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_GREEN, VGA_C_BLACK)
		);


		term.printk("     ");
		for (uint8_t x = 0; x < 32; x++) {
			if (x != 0)
				term.putc(' ');
			if (x == 16)
				term.putc(' ');
			term.printk("%x", x % 16);
		}
		term.printk("\n   *");
		for (uint8_t x = 0; x < 65; x++) {
			term.putc('-');
		}
		term.printk("\n");
		for (uint8_t y = 0; y < 16; y += 2) {
			term.printk("%xx | ", y);
			for (uint8_t x = 0; x < 32; x++) {
				if (x != 0)
					term.putc(' ');
				if (x == 16)
					term.putc(' ');
				term.putc('\xff');
				term.putc((char) ((y << 4) + x));
			}
			term.putc('\n');
			term.scrollToCursor();
		}

		term.setActive(true);
		while (__DEMO_RUN__)
			handleKeyboard(&term);
		return 0;
	}

	int	demo4() {
		CommandPrompt term = CommandPrompt(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_GREEN, VGA_C_BLACK)
		);

		for (size_t line = 0; __42__[line]; line++)
			term.put(__42__[line]);
		term.put("\n");

		term.resetCommand();
		term.flush();
		term.setActive(true);
		while (__DEMO_RUN__)
			handleKeyboard(&term);
		return 0;
	}
	
	int demo3() {
		Term term = Term(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_GREEN, VGA_C_BLACK)
		);
		Gdt gdt;
		
		term.printk("GDT Demo\n");
		
		term.setActive(true);
		gdt.set_entry(gdt.create_descriptor(0, 0, 0)); // Null segment
		gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0))); // Kernel code segment
		gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0))); // Kernel data segment
		gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3))); // User code segment
		gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3))); // User data segment
		gdt.loadGDT();
		
		term.printk("\nGDT Hexdump:\n");
		term.hexdump((void*)gdt.getGdtEntries(), sizeof(uint64_t[5]));
		
		struct gdt_ptr gdtr;
		get_gdt_ptr(&gdtr);
		term.printk("\n\nGDT address: %p\n", (void*)gdtr.base);
		
		term.printk("\nData 0x00000800 Hexdump:\n");
		term.hexdump((void*)0x00000800, sizeof(uint64_t[5]));
		term.printk("\nGDTR Hexdump:\n");
		term.hexdump((void*)gdtr.base, gdtr.limit + 1);
		
		
		while (1)
		handleKeyboard(&term);
		return 0;
	}
}