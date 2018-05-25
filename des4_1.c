/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des4_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 09:14:38 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/03 09:14:38 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_b64_d(t_elem *new)
{
	int *res;
	int y;
	int i;
	int k;

	i = 0;
	k = 0;
	if ((*new).rd == 0)
		(*new).prev_rd -= 1;
	y = ((*new).prev_rd / 4);
	while (i < (*new).prev_rd)
	{
		res = d_64(&(((*new).prev)[i]), &((*new).prev_rd));
		i += 4;
		((*new).prev)[k++] = ((res[0] << 6) | res[1]) >> 4;
		((*new).prev)[k++] = (((res[1] & 15) << 6) | res[2]) >> 2;
		((*new).prev)[k++] = (((res[2] & 3) << 6) | res[3]);
		ft_memdel((void**)(&res));
	}
	if ((*new).prev_rd > 0)
		(*new).prev_rd -= y;
}

void	ft_ecb_h(t_elem *new, int *f, t_k k)
{
	if (f[0] == 2)
	{
		if (f[1] == 1)
			ft_b64_d(new);
		des_ecb_d(new, k, 1);
		write(f[3], (*new).prev, (*new).prev_rd);
	}
	else
	{
		ft_str_hex(new, k);
		ft_ecb_out((*new).prev_rd, (*new).prev, f, &((*new).b));
		if ((*new).rd == 0 && (*new).p == 24)
		{
			ft_h2((*new).prev_rd, k, &((*new).str));
			if (f[1] == 1)
				ft_b64((*new).str, 8, f[3], &((*new).b));
			else
				write(f[3], (*new).str, 8);
		}
		if ((*new).rd == 0 && f[1] == 1 && (*new).b != 0)
			write(f[3], "\n", 1);
	}
}

void	ft_cbc_h2(t_elem new, unsigned long long k, unsigned long long v)
{
	unsigned long long	c;
	int					j;

	c = 0;
	j = -1;
	ft_pad_m(&c, &(new.prev_rd), 1);
	c ^= v;
	c = ft_message(c, k);
	while (++j < 8)
		(new.str)[j] = (c >> ((8 - (j + 1)) * 8)) & 255;
}

void	ft_cbc(t_elem *new, int *f, unsigned long long k,
	unsigned long long *v)
{
	if (f[0] == 2)
	{
		if (f[1] == 1)
			ft_b64_d(new);
		des_cbc_d(new, k, v, 1);
		write(f[3], (*new).prev, (*new).prev_rd);
	}
	else
	{
		ft_str_hex_cbc(k, new, v, 1);
		ft_ecb_out((*new).prev_rd, (*new).prev, f, &((*new).b));
		if ((*new).rd == 0 && (*new).p == 24)
		{
			ft_cbc_h2(*new, k, *v);
			if (f[1] == 1)
				ft_b64((*new).str, 8, f[3], &((*new).b));
			else
				write(f[3], (*new).str, 8);
		}
		if ((*new).rd == 0 && f[1] == 1 && (*new).b != 0)
			write(f[3], "\n", 1);
	}
}

void	ft_h1_cbc(int *r, unsigned long long *c, unsigned char **str,
	unsigned long long k)
{
	int j;

	*c = ft_message(*c, k);
	j = -1;
	while (++j < 8 && (*r += 1))
		(*str)[*r - 1] = (*c >> ((7 - j) * 8)) & 255;
}
