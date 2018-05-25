/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des6_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:28:52 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/04 16:28:52 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_read(int *f, int *i)
{
	char s;

	read(f[2], &s, 1);
	*i = 0;
}

void	ft_cbc_h3(t_h *h, char **argv, t_k *k)
{
	int num_k;
	int rd;

	rd = 0;
	(*h).f = (int*)malloc(sizeof(int) * 6);
	while (rd < 6)
		(*h).f[rd++] = 0;
	ft_cbc_flags(h, argv, 0);
	if ((*h).f[4] == 0)
	{
		(*h).key = ft_strnew(48);
		ft_read_key(&((*h).key));
		ft_key_iv(&((*h).key), &((*h).k), NULL, 1);
	}
	if ((*h).f[5] == 0)
	{
		(*h).iv = ft_strnew(16);
		write(1, "enter initial vector: ", 22);
		read(1, (*h).iv, 16);
		ft_key_iv(&((*h).iv), &((*h).v), NULL, 1);
	}
	num_k = ft_break_key(k, (*h).key, 48);
	ft_strdel(&(h->key));
	ft_get_keys(k, num_k);
}

void	ft_h1_cbc3(int *r, unsigned long long *c, unsigned char **str, t_k k)
{
	int j;

	*c = ft_message(*c, k.k1);
	*c = ft_message_r(*c, k.k2);
	*c = ft_message(*c, k.k3);
	j = -1;
	while (++j < 8 && (*r += 1))
		(*str)[*r - 1] = (*c >> ((7 - j) * 8)) & 255;
}

void	ft_des3_d(unsigned long long *c, t_k k)
{
	*c = ft_message_r(*c, k.k3);
	*c = ft_message(*c, k.k2);
	*c = ft_message_r(*c, k.k1);
}

void	des_cbc_d3(t_elem *new, t_k k, unsigned long long *v)
{
	int					i;
	int					j;
	int					r;
	unsigned long long	c;
	unsigned long long	c1;

	i = 0;
	r = 0;
	while (i < (*new).prev_rd)
	{
		j = -1;
		c = 0;
		while (++j < 8 && i < (*new).prev_rd)
			c = (c << 8) + ((*new).prev)[i++];
		c1 = c;
		ft_des3_d(&c, k);
		j = -1;
		c ^= *v;
		while (++j < 8 && (r += 1))
			((*new).prev)[r - 1] = (c >> ((8 - (j + 1)) * 8)) & 255;
		*v = c1;
	}
	if ((*new).rd == 0)
		(*new).prev_rd -= ((*new).prev)[r - 1];
}
