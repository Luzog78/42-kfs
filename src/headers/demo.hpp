/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/28 02:34:59 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_HPP
#define DEMO_HPP

#ifndef DEMO_NO
# define DEMO_NO	1
#endif
#if DEMO_NO == 1
# define DEMO_FUNC	demo1
#elif DEMO_NO == 2
# define DEMO_FUNC	demo2
#else
# define DEMO_FUNC	demoErr
#endif

int	demoErr();
int	demo1();
int	demo2();

#endif
