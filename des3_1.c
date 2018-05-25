/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:13:19 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/15 19:14:40 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_pad_m(unsigned long long *c, int *rd, int k)
{
	int	j;
	int	t;

	j = 0;
	t = 8 - (*rd % 8);
	if (t < 8)
	{
		*rd += t;
		while (j++ < t)
			(*c) = ((*c) << 8) | t;
	}
	else if (k == 1)
	{
		*rd += t;
		while (j++ < t)
			(*c) = ((*c) << 8) | t;
	}
}

void	ft_des_flags(int **f, char **argv, char **key)
{
	int i;

	i = 0;
	(*f)[3] = 1;
	(*f)[0] = 1;
	while (argv && argv[++i])
	{
		if (ft_strcmp(argv[i], "-d") == 0)
			(*f)[0] = 2;
		else if (ft_strcmp(argv[i], "-a") == 0)
			(*f)[1] = 1;
		else if (ft_strcmp(argv[i], "-i") == 0)
			(*f)[2] = open(argv[++i], O_RDONLY);
		else if (ft_strcmp(argv[i], "-o") == 0)
			(*f)[3] = open(argv[++i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (ft_strcmp(argv[i], "-k") == 0)
		{
			*key = ft_strdup(argv[++i]);
			(*f)[4] = 1;
		}
	}
}

void	ft_h2(int prev_rd, t_k k, unsigned char **str)
{
	unsigned long long	c;
	int					j;

	c = 0;
	j = -1;
	ft_pad_m(&c, &prev_rd, 1);
	c = ft_message(c, k.k1);
	c = ft_message_r(c, k.k2);
	c = ft_message(c, k.k3);
	while (++j < 8)
		(*str)[j] = (c >> ((8 - (j + 1)) * 8)) & 255;
}

void	ft_h1(int *r, unsigned long long c, unsigned char **str,
	t_k k)
{
	int j;

	c = ft_message(c, k.k1);
	c = ft_message_r(c, k.k2);
	c = ft_message(c, k.k3);
	j = -1;
	while (++j < 8 && (*r += 1))
		(*str)[*r - 1] = (c >> ((7 - j) * 8)) & 255;
}

void	ft_str_hex(t_elem *new, t_k k)
{
	int					i;
	int					j;
	int					r;
	unsigned long long	c;

	i = 0;
	r = 0;
	while (i < (*new).p)
	{
		c = 0;
		j = -1;
		while (++j < 8 && i < (*new).prev_rd)
			c = (c << 8) + ((*new).prev)[i++];
		if (i >= (*new).p && (*new).rd == 0)
			ft_pad_m(&c, &((*new).prev_rd), 0);
		ft_h1(&r, c, &((*new).prev), k);
	}
	if ((*new).p < 24 && i % 8 == 0)
	{
		ft_pad_m(&c, &((*new).prev_rd), 1);
		ft_h1(&r, c, &((*new).prev), k);
	}
}
