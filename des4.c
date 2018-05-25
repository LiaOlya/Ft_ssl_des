/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:53:49 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/15 19:15:17 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void			des_ecb_d(t_elem *new, t_k k, int f)
{
	int					i;
	int					j;
	int					r;
	unsigned long long	c;

	i = 0;
	r = 0;
	while (i < (*new).prev_rd)
	{
		j = -1;
		c = 0;
		while (++j < 8 && i < (*new).prev_rd)
			c = (c << 8) + ((*new).prev)[i++];
		c = ft_message_r(c, k.k3);
		c = ft_message(c, k.k2);
		c = ft_message_r(c, k.k1);
		j = -1;
		while (++j < 8 && (r += 1))
			((*new).prev)[r - 1] = (c >> ((7 - j) * 8)) & 255;
	}
	if ((*new).rd == 0 && f == 1)
		(*new).prev_rd -= ((*new).prev)[r - 1];
}

void			ft_des_ecb_h(char **argv, int **f, t_k *k, int ch)
{
	int		num_k;
	char	*key;
	int		rd;

	rd = 0;
	*f = (int*)malloc(sizeof(int) * 5);
	while (rd < 5)
		(*f)[rd++] = 0;
	ft_des_flags(f, argv, &key);
	if ((*f)[4] == 0)
	{
		key = ft_strnew(ch);
		ft_read_key(&key);
	}
	num_k = ft_break_key(k, key, ch);
	ft_strdel(&key);
	ft_get_keys(k, num_k);
}

void			ft_del(t_elem new, int *f)
{
	ft_strdel((char**)(&(new.prev)));
	ft_strdel((char**)(&(new.str)));
	ft_memdel((void**)(&f));
}

void			ft_cpy(unsigned char **dst, unsigned char *src, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		(*dst)[i] = src[i];
		++i;
	}
}

void			ft_des_ecb(char **argv, int ch)
{
	t_elem				new;
	int					*f;
	t_k					k;

	ft_des_ecb_h(argv, &f, &k, ch);
	if (f[0] == 2 && f[1] == 1)
	{
		ft_64d(f, k);
		return ;
	}
	ft_new(&new, f, 24);
	while (new.prev_rd > 0)
	{
		new.p = new.prev_rd;
		new.rd = read(f[2], new.str, 24);
		if (new.rd == 1 && (new.str)[0] == '\n' && f[0] == 2 && f[1] == 1)
			new.rd = 0;
		new.str[new.rd] = '\0';
		ft_ecb_h(&new, f, k);
		new.prev_rd = new.rd;
		ft_cpy(&(new.prev), new.str, new.rd);
	}
	ft_close(f[2], f[3]);
	ft_del(new, f);
}
