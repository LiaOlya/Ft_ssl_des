/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des5_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:28:40 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/04 16:28:40 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void				ft_pad24(t_elem *new, unsigned long long c,
	unsigned long long *v, unsigned long long k)
{
	int r;

	r = 0;
	ft_pad_m(&c, &((*new).prev_rd), 1);
	c ^= *v;
	ft_h1_cbc(&r, &c, &((*new).prev), k);
}

unsigned long long	ft_message_r(unsigned long long m, unsigned long long k1)
{
	unsigned long long l;
	unsigned long long l1;
	unsigned long long r;
	unsigned long long *k;
	unsigned long long r1;

	m = ft_ip_p(m, 1);
	k = ft_subkeys(k1);
	l = m >> 32;
	r = m & 4294967295;
	k1 = 16;
	while (k1 > 0)
	{
		l1 = r;
		r1 = l ^ (ft_s_modif(k[k1] ^ ft_e_sel(r)));
		--k1;
		r = r1;
		l = l1;
	}
	r = (r << 32) | l;
	r = ft_ip_p(r, 3);
	ft_memdel((void**)(&k));
	return (r);
}

void				ft_ecb_out(int prev_rd, unsigned char *str, int *f, int *b)
{
	if (f[1] == 1)
		ft_b64(str, prev_rd, f[3], b);
	else
		write(f[3], str, prev_rd);
}

void				ft_64d_cbc(t_h h)
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
		ft_cbc(&new, h.f, h.k, &(h.v));
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
		if (i == 2)
			ft_read(h.f, &i);
	}
	ft_del(new, h.f);
}

void				ft_64d(int *f, t_k k)
{
	int		i;
	t_elem	new;

	ft_new(&new, f, 32);
	i = 1;
	while (new.prev_rd > 0)
	{
		new.p = new.prev_rd;
		new.rd = read(f[2], new.str, 32);
		if (new.rd == 1 && (new.str)[0] == '\n')
			new.rd = 0;
		i += 1;
		new.str[new.rd] = '\0';
		ft_ecb_h(&new, f, k);
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
		if (i == 2)
			ft_read(f, &i);
	}
	ft_close(f[2], f[3]);
	ft_del(new, f);
}
