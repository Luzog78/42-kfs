/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:13:38 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/04 12:00:44 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_HPP
#define DEMO_HPP

#ifndef DEMO_NO
# define DEMO_NO	3
#endif
#if DEMO_NO == 1
# define DEMO_FUNC	demo1
#elif DEMO_NO == 2
# define DEMO_FUNC	demo2
#elif DEMO_NO == 3
# define DEMO_FUNC	demo3
#else
# define DEMO_FUNC	demoErr
#endif

int	demoErr();
int	demo1();
int	demo2();
int	demo3();

#endif
