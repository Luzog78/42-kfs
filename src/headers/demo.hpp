/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/09 04:47:56 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_HPP
#define DEMO_HPP

#ifndef DEMO_NO
# define DEMO_NO	1
#endif

extern int	__DEMO_NO__;
extern bool	__DEMO_RUN__;

namespace Demo {
	int	demoErr();
	int	demo1();
	int	demo2();
	int	demo4();
	
	int	(*demo(int no = __DEMO_NO__))();
}

#endif
