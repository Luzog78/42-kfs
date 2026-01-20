/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/20 16:37:07 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
	// Kernel main function

	asm volatile (
		"movl $0x2f4b2f4f, 0xb8000\n" // Write 'OK' to the screen in green text
	);

	while (1)
	{
		asm volatile ("hlt"); // Halt the CPU to save power
	}
	return 0;
}
