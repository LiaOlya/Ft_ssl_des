/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:53:29 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/09 08:48:17 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

int				ft_flags(char **argv, int *in, int *out)
{
	int res;
	int i;

	i = 1;
	res = 0;
	while (argv && argv[i])
	{
		if (ft_strcmp(argv[i], "-e") == 0)
			res = 1;
		if (ft_strcmp(argv[i], "-d") == 0 || ft_strcmp(argv[i], "-D") == 0)
			res = 2;
		if (ft_strcmp(argv[i], "-i") == 0)
			*in = open(argv[i + 1], O_RDONLY);
		if (ft_strcmp(argv[i], "-o") == 0)
			*out = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		++i;
	}
	return (res);
}

void			base64(unsigned char *str, int fd, int k)
{
	int res;

	res = str[0] >> 2;
	write(fd, &BASE[res], 1);
	res = (((str[0] & 3) << 8) | str[1]) >> 4;
	write(fd, &BASE[res], 1);
	if (k > 1)
	{
		res = (((str[1] & 15) << 8) | str[2]) >> 6;
		write(fd, &BASE[res], 1);
	}
	else
		write(fd, "=", 1);
	if (k > 2)
	{
		res = str[2] & 63;
		write(fd, &BASE[res], 1);
	}
	else
		write(fd, "=", 1);
}

unsigned char	*reall(unsigned char *str, unsigned char *res)
{
	int				i;
	int				j;
	unsigned char	*new;

	if (res)
		i = ft_strlen((char*)res);
	else
		i = 0;
	new = (unsigned char*)ft_strnew(i + 4);
	j = 0;
	while (j < i)
	{
		new[j] = res[j];
		++j;
	}
	if (res != NULL)
		ft_strdel((char**)(&res));
	i = 0;
	while (i < 3)
		new[j++] = str[i++];
	new[j] = '\0';
	return (new);
}

void			ft_h(int *res, unsigned char **s)
{
	(*s)[0] = ((res[0] << 6) | res[1]) >> 4;
	(*s)[1] = (((res[1] & 15) << 6) | res[2]) >> 2;
	(*s)[2] = (((res[2] & 3) << 6) | res[3]);
	(*s)[3] = '\0';
}

void			rev64(unsigned char **s, unsigned char **r, int *g)
{
	int *res;
	int	i;

	i = 2;
	res = d_64(*s, &i);
	if (res == NULL)
	{
		*g = 1;
		ft_memdel((void**)(&res));
		return ;
	}
	ft_h(res, s);
	*r = reall(*s, *r);
	ft_memdel((void**)(&res));
}
