/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 20:58:42 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/20 20:58:43 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

int		ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char*)str;
	i = -1;
	while (++i < len)
		s[i] = (unsigned char)c;
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
