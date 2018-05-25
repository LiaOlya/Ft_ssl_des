/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des1_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:08:46 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:11:23 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

unsigned long long	ft_ip(unsigned long long a)
{
	static int			ip[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52,
		44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40,
		32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19,
		11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
	unsigned long long	res;
	int					i;

	res = 0;
	i = -1;
	while (++i < 64)
		res = ((res << 1) | ((a >> (64 - ip[i])) & 1));
	return (res);
}

unsigned long long	ft_f_p(unsigned long long a)
{
	static int			f_p[64] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15,
		23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22,
		11, 4, 25};
	unsigned long long	res;
	int					i;

	res = 0;
	i = -1;
	while (++i < 32)
		res = ((res << 1) | ((a >> (32 - f_p[i])) & 1));
	return (res);
}

unsigned long long	ft_ip_1(unsigned long long a)
{
	static int			ip_1[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7,
		47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13,
		53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19,
		59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
	unsigned long long	res;
	int					i;

	res = 0;
	i = -1;
	while (++i < 64)
		res = ((res << 1) | ((a >> (64 - ip_1[i])) & 1));
	return (res);
}

unsigned long long	ft_ip_p(unsigned long long a, int n)
{
	unsigned long long	res;
	int					i;

	i = -1;
	res = 0;
	if (n == 1)
		res = ft_ip(a);
	else if (n == 2)
		res = ft_f_p(a);
	else if (n == 3)
		res = ft_ip_1(a);
	return (res);
}

unsigned long long	ft_e_sel(unsigned long long a)
{
	static int			ip[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9,
		10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20,
		21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
	unsigned long long	res;
	int					i;

	i = -1;
	res = 0;
	while (++i < 48)
		res = ((res << 1) | ((a >> (32 - ip[i])) & 1));
	return (res);
}
