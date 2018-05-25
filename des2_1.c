/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des2_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:06:07 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:06:39 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

unsigned long long	ft_s5(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};
	int			c;
	int			r;

	r = (((a >> (3 * 6 + 5)) & 1) << 1) | ((a >> 3 * 6) & 1);
	c = (a >> (3 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s6(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};
	int			c;
	int			r;

	r = (((a >> (2 * 6 + 5)) & 1) << 1) | ((a >> 2 * 6) & 1);
	c = (a >> (2 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s7(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};
	int			c;
	int			r;

	r = (((a >> (6 + 5)) & 1) << 1) | ((a >> 6) & 1);
	c = (a >> (6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s8(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};
	int			c;
	int			r;

	r = (((a >> 5) & 1) << 1) | (a & 1);
	c = (a >> 1) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s_modif(unsigned long long a)
{
	unsigned long long	res;

	res = 0;
	res = ft_s1(a, res);
	res = ft_s2(a, res);
	res = ft_s3(a, res);
	res = ft_s4(a, res);
	res = ft_s5(a, res);
	res = ft_s6(a, res);
	res = ft_s7(a, res);
	res = ft_s8(a, res);
	res = ft_ip_p(res, 2);
	return (res);
}
