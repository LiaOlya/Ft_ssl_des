/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:28:32 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/04 16:28:32 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_str_hex_cbc(unsigned long long k, t_elem *new,
	unsigned long long *v, int ch)
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
		if (i[0] >= p && i[0] % 8 != 0 && ch == 1)
			ft_pad_m(&c, &((*new).prev_rd), 0);
		c ^= *v;
		ft_h1_cbc(&i[2], &c, &((*new).prev), k);
		*v = c;
	}
	if (p < 24 && i[0] % 8 == 0 && ch == 1)
	{
		ft_pad_m(&c, &((*new).prev_rd), 1);
		c ^= *v;
		ft_h1_cbc(&i[2], &c, &((*new).prev), k);
	}
}

void	ft_cbc_flags(t_h *h, char **argv, int ch)
{
	int i;

	i = 0;
	(*h).f[3] = 1;
	(*h).f[0] = 1;
	while (argv && argv[++i])
	{
		if (ft_strcmp(argv[i], "-d") == 0)
			(*h).f[0] = 2;
		else if (ft_strcmp(argv[i], "-a") == 0)
			(*h).f[1] = 1;
		else if (ft_strcmp(argv[i], "-i") == 0)
			(*h).f[2] = open(argv[i + 1], O_RDONLY);
		else if (ft_strcmp(argv[i], "-o") == 0)
			(*h).f[3] = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (ft_strcmp(argv[i], "-k") == 0 && ((*h).f[4] = 1))
			ft_key_iv(&((*h).key), &((*h).k), argv[++i], ch);
		else if (ft_strcmp(argv[i], "-v") == 0 && ((*h).f[5] = 1))
			ft_key_iv(&((*h).iv), &((*h).v), argv[++i], 1);
	}
}

void	ft_cbc_h(t_h *h, char **argv, int ch)
{
	int rd;

	rd = 0;
	(*h).f = (int*)malloc(sizeof(int) * 6);
	while (rd < 6)
		(*h).f[rd++] = 0;
	ft_cbc_flags(h, argv, ch);
	if ((*h).f[4] == 0)
	{
		(*h).key = ft_strnew(16);
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
}

void	des_cbc_d(t_elem *new, unsigned long long k, unsigned long long *v,
	int ch)
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
		c = ft_message_r(c, k);
		j = -1;
		c ^= *v;
		while (++j < 8 && (r += 1))
			((*new).prev)[r - 1] = (c >> ((8 - (j + 1)) * 8)) & 255;
		*v = c1;
	}
	if ((*new).rd == 0 && ch == 1)
		(*new).prev_rd -= ((*new).prev)[r - 1];
}

void	ft_des_cbc(char **argv)
{
	t_elem	new;
	t_h		h;

	ft_cbc_h(&h, argv, 1);
	h.k = ft_pc(h.k, 1);
	if (h.f[0] == 2 && h.f[1] == 1)
	{
		ft_64d_cbc(h);
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
		ft_cbc(&new, (h.f), h.k, &(h.v));
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
	}
	ft_close((h.f)[2], (h.f)[3]);
	ft_del(new, (h.f));
}
