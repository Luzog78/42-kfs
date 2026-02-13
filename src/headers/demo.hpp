/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 13:30:17 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_HPP
#define DEMO_HPP

#ifndef DEMO_NO
# define DEMO_NO	3
#endif

extern int	__DEMO_NO__;
extern bool	__DEMO_RUN__;

namespace Demo {
	int	demoErr();
	int	demo1();
	int	demo2();
	int demo3();
	int	demo4();
	
	int	(*demo(int no = __DEMO_NO__))();
}

#endif
