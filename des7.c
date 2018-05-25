/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 20:22:32 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/20 20:22:32 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_str_hex_cbc3(t_k k, t_elem *new, unsigned long long *v)
{
	int					p;
	int					i[3];
	unsigned long long	c;

	i[0] = 0;
	i[2] = 0;
	p = (*new).prev_rd;
	while (i[0] < p)
	{
		c = 0;
		i[1] = -1;
		while (++i[1] < 8 && i[0] < (*new).prev_rd)
			c = (c << 8) + ((*new).prev)[i[0]++];
		if (i[0] >= p && i[0] % 8 != 0)
			ft_pad_m(&c, &((*new).prev_rd), 0);
		c ^= *v;
		ft_h1_cbc3(&i[2], &c, &((*new).prev), k);
		*v = c;
	}
	if (p < 24 && i[0] % 8 == 0)
	{
		ft_pad_m(&c, &((*new).prev_rd), 1);
		c ^= *v;
		ft_h1_cbc3(&i[2], &c, &((*new).prev), k);
	}
}

void	ft_cbc_h23(t_elem new, t_k k, unsigned long long v)
{
	unsigned long long	c;
	int					j;

	c = 0;
	j = -1;
	ft_pad_m(&c, &(new.prev_rd), 1);
	c ^= v;
	c = ft_message(c, k.k1);
	c = ft_message_r(c, k.k2);
	c = ft_message(c, k.k3);
	while (++j < 8)
		(new.str)[j] = (c >> ((8 - (j + 1)) * 8)) & 255;
}

void	ft_cbc3(t_elem *new, int *f, t_k keys, unsigned long long *v)
{
	if (f[0] == 2)
	{
		if (f[1] == 1)
			ft_b64_d(new);
		des_cbc_d3(new, keys, v);
		write(f[3], (*new).prev, (*new).prev_rd);
	}
	else
	{
		ft_str_hex_cbc3(keys, new, v);
		ft_ecb_out((*new).prev_rd, (*new).prev, f, &((*new).b));
		if ((*new).rd == 0 && (*new).p == 24)
		{
			ft_cbc_h23(*new, keys, *v);
			if (f[1] == 1)
				ft_b64((*new).str, 8, f[3], &((*new).b));
			else
				write(f[3], (*new).str, 8);
		}
		if ((*new).rd == 0 && f[1] == 1 && (*new).b != 0)
			write(f[3], "\n", 1);
	}
}

void	ft_64d_cbc3(t_h h, t_k k)
{
	int		i;
	t_elem	new;

	ft_new(&new, h.f, 32);
	i = 1;
	while (new.prev_rd > 0)
	{
		new.p = new.prev_rd;
		new.rd = read((h.f)[2], new.str, 32);
		if (new.rd == 1 && (new.str)[0] == '\n')
			new.rd = 0;
		i += 1;
		new.str[new.rd] = '\0';
		ft_cbc3(&new, h.f, k, &(h.v));
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
		if (i == 2)
			ft_read(h.f, &i);
	}
	ft_del(new, h.f);
}

void	ft_des3(char **argv)
{
	t_elem	new;
	t_h		h;
	t_k		k;

	ft_cbc_h3(&h, argv, &k);
	if (h.f[0] == 2 && h.f[1] == 1)
	{
		ft_64d_cbc3(h, k);
		return ;
	}
	ft_new(&new, h.f, 24);
	while (new.prev_rd > 0)
	{
		new.p = new.prev_rd;
		new.rd = read((h.f)[2], new.str, 24);
		if (new.rd == 1 && (new.str)[0] == '\n' && h.f[0] == 2 && h.f[1] == 1)
			new.rd = 0;
		new.str[new.rd] = '\0';
		ft_cbc3(&new, (h.f), k, &(h.v));
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
	}
	ft_close((h.f)[2], (h.f)[3]);
	ft_del(new, (h.f));
}
