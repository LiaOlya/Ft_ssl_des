/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:28:46 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/04 16:28:47 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_new(t_elem *new, int *f, int n)
{
	(*new).str = (unsigned char*)ft_strnew(n);
	(*new).prev = (unsigned char *)ft_strnew(n);
	(*new).prev_rd = read(f[2], (*new).prev, n);
	(*new).prev[(*new).prev_rd] = '\0';
	(*new).b = 0;
}

int		ft_2(int k, unsigned char **r, unsigned char **buf, int i)
{
	int g;

	g = 0;
	rev64(buf, r, &g);
	if (k != i || g == 1)
	{
		ft_strdel((char**)(buf));
		return (1);
	}
	return (0);
}

void	ft_key_iv(char **k, unsigned long long *l, char *argv, int ch)
{
	if (argv != NULL)
		*k = ft_strdup(argv);
	if (ch == 1)
	{
		ft_pad_key(k);
		*l = ft_strtol(*k);
		ft_strdel(k);
	}
}

int		ft_break_key(t_k *k, char *key, int ch)
{
	int i;
	int x;
	int j;
	int len;
	int num_k;

	i = 0;
	num_k = 1;
	while (i < ch && key[i++])
		if (i == 17 || i == 33)
			++num_k;
	len = i;
	i = -1;
	x = 0;
	while (++i < num_k)
	{
		j = 0;
		((*k).keys)[i] = ft_strnew(16);
		while (j < 16 && x < len)
			((*k).keys)[i][j++] = key[x++];
		((*k).keys)[i][j++] = '\0';
	}
	ft_pad_key(&(((*k).keys)[num_k - 1]));
	return (num_k);
}

void	ft_get_keys(t_k *k, int num_k)
{
	(*k).k1 = ft_pc(ft_strtol(((*k).keys)[0]), 1);
	if (num_k > 1)
		(*k).k2 = ft_pc(ft_strtol(((*k).keys)[1]), 1);
	else
		(*k).k2 = 0;
	if (num_k > 2)
		(*k).k3 = ft_pc(ft_strtol(((*k).keys)[2]), 1);
	else
		(*k).k3 = 0;
	ft_strdel(&((*k).keys)[0]);
	if (num_k > 1)
		ft_strdel(&((*k).keys)[1]);
	if (num_k > 2)
		ft_strdel(&((*k).keys)[2]);
}
