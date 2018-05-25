/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:53:40 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:07:17 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

unsigned long long	*ft_subkeys(unsigned long long k)
{
	unsigned long long	*res;
	unsigned long long	c;
	unsigned long long	d;
	int					i;
	int					n;

	res = (unsigned long long*)malloc(sizeof(unsigned long long) * 17);
	res[0] = k;
	c = k >> 28;
	d = k & 268435455;
	i = 0;
	while (++i <= 16)
	{
		if (i == 1 || i == 2 || i == 9 || i == 16)
			n = 1;
		else
			n = 2;
		c = ((c << n) & 268435455) | (c >> (28 - n));
		d = ((d << n) & 268435455) | (d >> (28 - n));
		res[i] = ft_pc(((c << 28) | d), 2);
	}
	return (res);
}

unsigned long long	ft_s1(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13,
		6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11,
		3, 14, 10, 0, 6, 13};
	int			c;
	int			r;

	r = (((a >> (7 * 6 + 5)) & 1) << 1) | ((a >> 7 * 6) & 1);
	c = (a >> (7 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s2(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};
	int			c;
	int			r;

	r = (((a >> (6 * 6 + 5)) & 1) << 1) | ((a >> 6 * 6) & 1);
	c = (a >> (6 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s3(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};
	int			c;
	int			r;

	r = (((a >> (5 * 6 + 5)) & 1) << 1) | ((a >> 5 * 6) & 1);
	c = (a >> (5 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}

unsigned long long	ft_s4(unsigned long long a, unsigned long long res)
{
	static int	s[64] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};
	int			c;
	int			r;

	r = (((a >> (4 * 6 + 5)) & 1) << 1) | ((a >> 4 * 6) & 1);
	c = (a >> (4 * 6 + 1)) & 15;
	res = (res << 4) + s[(r * 16) + c];
	return (res);
}
