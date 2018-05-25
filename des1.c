/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:53:35 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:10:02 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

unsigned long long	ft_strtol(char *str)
{
	unsigned int		temp;
	unsigned long long	a;
	int					i;

	i = 0;
	a = 0;
	while (str[i] && i < 16)
	{
		temp = str[i++];
		if (temp >= 48 && temp <= 57)
			temp -= 48;
		else if (temp >= 97 && temp <= 102)
			temp -= 87;
		else if (temp >= 65 && temp <= 70)
			temp -= 55;
		if (temp > 15)
			return (0);
		a = a | temp;
		if (i < 16)
			a = a << 4;
	}
	if (i < 16)
		a = a >> 4;
	return (a);
}

unsigned long long	ft_pc(unsigned long long a, int n)
{
	static int			pc_1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42,
		34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63,
		55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45,
		37, 29, 21, 13, 5, 28, 20, 12, 4};
	static int			pc_2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21,
		10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47,
		55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36,
		29, 32};
	unsigned long long	res;
	int					i;

	res = 0;
	i = -1;
	if (n == 1)
	{
		while (++i < 56)
			res = ((res << 1) | ((a >> (64 - pc_1[i])) & 1));
	}
	else
	{
		while (++i < 48)
			res = ((res << 1) | ((a >> (56 - pc_2[i])) & 1));
	}
	return (res);
}
