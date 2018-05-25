/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:53:45 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:13:43 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

unsigned long long	ft_message(unsigned long long m, unsigned long long k1)
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
	k1 = 0;
	while (k1 < 16)
	{
		l1 = r;
		r1 = l ^ (ft_s_modif(k[k1 + 1] ^ ft_e_sel(r)));
		++k1;
		r = r1;
		l = l1;
	}
	r = (r << 32) | l;
	r = ft_ip_p(r, 3);
	ft_memdel((void**)(&k));
	return (r);
}

void				ft_pad_key(char **t)
{
	int i;
	int l;

	l = ft_strlen(*t);
	i = l;
	while (i < 16)
		(*t)[i++] = 0 + '0';
	(*t)[i] = '\0';
}

void				ft_read_key(char **key)
{
	const char	*prompt;
	char		*tmp;
	char		*tmp1;

	prompt = ft_strnew(16);
	write(1, "enter des key in hex:", 21);
	tmp = getpass(prompt);
	tmp1 = ft_strdup(tmp);
	write(1, "Verifying - enter des key in hex:", 33);
	tmp = getpass(prompt);
	if (ft_strcmp(tmp, tmp1) != 0)
		return ;
	*key = tmp;
	ft_strdel((char**)(&prompt));
	ft_strdel(&tmp1);
}

void				ft_b64(unsigned char *str, int l, int out, int *b)
{
	int				i;
	int				j;
	unsigned char	*tmp;

	i = 0;
	while (i < l)
	{
		tmp = (unsigned char*)ft_strnew(3);
		j = 0;
		while (i < l && j < 3)
			tmp[j++] = str[i++];
		base64(tmp, out, j);
		*b += 4;
		if (*b == 64)
		{
			write(out, "\n", 1);
			*b = 0;
		}
		ft_strdel((char**)(&tmp));
	}
}

int					*d_64(unsigned char *s, int *prev_rd)
{
	int *res;
	int i;
	int j;

	res = (int*)malloc(sizeof(int) * 4);
	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (BASE[j] && BASE[j] != s[i])
			++j;
		if (s[i] == '=' && (!s[i + 1] || s[i + 1] == '\n' || s[i + 1] == '=')
			&& (*prev_rd -= 1))
		{
			res[i] = 0;
			if (s[i + 1] && s[i + 1] == '=' && (!s[i + 2] || s[i + 2] == '\n')
				&& (*prev_rd -= 1))
				res[++i] = 0;
		}
		else if (j >= 64)
			return (NULL);
		else
			res[i] = j;
	}
	return (res);
}
