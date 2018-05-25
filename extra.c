/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 20:54:01 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/20 20:54:01 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

char	*ft_strnew(size_t size)
{
	char	*res;

	res = (char*)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	ft_memset(res, 0, size + 1);
	return (res);
}

void	ft_strdel(char **as)
{
	while (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

void	ft_memdel(void **ap)
{
	while (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			if (ft_isascii(s1[i]) && ft_isascii(s2[i]))
				return (s1[i] - s2[i]);
			else
				return (s2[i] - s1[i]);
		}
		++i;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
