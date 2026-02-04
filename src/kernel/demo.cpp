/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 23:17:49 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/04 11:43:43 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int	demoErr() {
	Term term = Term(
		Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
		Vect2<size_t>(0, 0),
		VGA::character(VGA_C_WHITE, VGA_C_LIGHT_RED)
	);

	term.put("Demo not found!\n");
	term.flush();
	return 1;
}

int	demo1() {
	Term terms[] = {
		Term(
			Vect2<size_t>(VGA_WIDTH, 17),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY)
		),
		Term(
			Vect2<size_t>(23, 8),
			Vect2<size_t>(0, 17),
			VGA::character(VGA_C_DARK_GREY, VGA_C_BLACK)
		),
		Term(
			Vect2<size_t>(32, 8),
			Vect2<size_t>(24, 17),
			VGA::character(VGA_C_LIGHT_GREY, VGA_C_BLACK)
		),
		Term(
			Vect2<size_t>(23, 8),
			Vect2<size_t>(57, 17),
			VGA::character(VGA_C_WHITE, VGA_C_LIGHT_GREY)
		),
		Term(
			Vect2<size_t>(VGA_WIDTH, VGA_HEIGHT),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_GREEN, VGA_C_BLACK)
		)
	};
	int activeTerm = 3;
	int shortcut = SHORTCUT_NONE;

	terms[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	terms[0].put("@                                                                              @");
	terms[0].put("@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @");
	terms[0].put("@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @");
	terms[0].put("@ | $$  | $$|__/  \\ $$       | $$   /$$| $$  \\__//$$$$$$$                      @");
	terms[0].put("@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @");
	terms[0].put("@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @");
	terms[0].put("@       | $$| $$             | $$_  $$ | $$     \\____  $$  | _ )_  _           @");
	terms[0].put("@       | $$| $$$$$$$$       | $$ \\  $$| $$     /$$$$$$$/  | _ \\ || | ysabik   @");
	terms[0].put("@       |__/|________/       |__/  \\__/|__/    |_______/   |___/\\_, | bsavinel @");
	terms[0].put("@                                                               |__/           @");
	terms[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	terms[0].put("\n");

	terms[0].put("You can switch between terminals with Ctrl+[1-5]!\n");
	terms[0].put("Type Alt+[0-f] Alt+[0-f] to write special characters using the CP437 ISO.\n", VGA::character(VGA_C_RED, VGA_C_CYAN));

	for (int i = 0; i <= UCHAR_MAX; i++) {
		terms[1].printk("%x ", i);
		terms[1].scrollToCursor();
	}

	for (uint16_t i = 0; i < 256; i++) {
		terms[2].putc('\xff');
		terms[2].putc((char) i);
		terms[2].scrollToCursor();
	}

	terms[3].put("*You can type here...*\n");
	terms[3].put("*Ctrl+5 for more space*\n");

	terms[4].put("\xff\xd5\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd", VGA::character(VGA_C_BLUE));
	terms[4].put(" Welcome to the big terminal! ", VGA::character(VGA_C_BLACK, VGA_C_BLUE));
	terms[4].put("\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xcd\xff\xb8", VGA::character(VGA_C_BLUE));
	terms[4].setCursor(Vect2<size_t>(0, 1));
	terms[4].put("\xff\xb3", VGA::character(VGA_C_BLUE));
	terms[4].setCursor(Vect2<size_t>(79, 1));
	terms[4].put("\xff\xb3", VGA::character(VGA_C_BLUE));
	terms[4].setCursor(Vect2<size_t>(2, 1));
	terms[4].put("*There is way more space here to tell the tale...*");
	terms[4].setCursor(Vect2<size_t>(0, 3));

	terms[0].flush();
	terms[1].flush();
	terms[2].flush();
	terms[3].flush();

	stack_check(true);
	terms[activeTerm].setActive(true);
	while (1) {
		if (activeTerm >= 0 && !terms[activeTerm].isActive())
			activeTerm = -1;
		shortcut = handleKeyboard(activeTerm >= 0 ? &terms[activeTerm] : nullptr);
		if (shortcut != SHORTCUT_NONE) {
			if (shortcut & FLAG_TERM_SWITCH && (shortcut & ~FLAG_TERM_SWITCH) < 5) {
				if (activeTerm >= 0)
					terms[activeTerm].setActive(false);
				activeTerm = (shortcut & ~FLAG_TERM_SWITCH);
				terms[activeTerm].setActive(true);
				terms[activeTerm].flush();
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
	while (1)
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
	gdt.create_descriptor(0, 0, 0); // Null segment
    gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0)); // Kernel code segment
    gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0)); // Kernel data segment
    gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3)); // User code segment
    gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3)); // User data segment
	gdt.loadGDT();

	while (1)
		handleKeyboard(&term);
	return 0;
}