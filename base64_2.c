/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:53:39 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/13 16:09:33 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	ft_b64_h(int *b, int out, unsigned char *buf, int k)
{
	base64(buf, out, k);
	*b += 4;
	if (*b == 64)
	{
		write(out, "\n", 1);
		*b = 0;
	}
}

int		ft_skip_64_nl(int in, unsigned char **buf, int i, int *a)
{
	char	s;
	int		k;

	if (i == 4)
	{
		*a += 4;
		if (*a == 64)
		{
			read(in, &s, 1);
			*a = 0;
		}
	}
	*buf = (unsigned char*)ft_strnew(i);
	k = read(in, *buf, i);
	return (k);
}

void	ft_1(int i, unsigned char **r, int in, int out)
{
	int				b;
	unsigned char	*buf;
	int				k;

	b = 0;
	buf = (unsigned char*)ft_strnew(i);
	k = read(in, buf, i);
	while (k > 0)
	{
		buf[i] = '\0';
		if (i != 4)
			ft_b64_h(&b, out, buf, k);
		else if (ft_2(k, r, &buf, i) == 1)
			return ;
		ft_strdel((char**)(&buf));
		k = ft_skip_64_nl(in, &buf, i, &b);
	}
	if (i != 4 && b != 0)
		write(out, "\n", 1);
	ft_strdel((char**)(&buf));
}

void	ft_close(int in, int out)
{
	if (in > 0)
		close(in);
	if (out > 1)
		close(out);
}

void	ft_64(char **argv)
{
	int				i;
	unsigned char	*r;
	int				in;
	int				out;

	in = 0;
	out = 1;
	i = 3;
	if (ft_flags(argv, &in, &out) == 2)
		i = 4;
	r = NULL;
	ft_1(i, &r, in, out);
	if (i == 4)
	{
		write(out, r, ft_strlen((const char*)r));
		ft_strdel((char**)(&r));
	}
	ft_close(in, out);
}
