/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:04:58 by oltkache          #+#    #+#             */
/*   Updated: 2018/03/14 16:14:12 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

int		check(char *str, char **argv)
{
	if (ft_strcmp(str, "base64") == 0)
		ft_64(argv);
	else if (ft_strcmp(str, "des-ecb") == 0)
		ft_des_ecb(argv, 16);
	else if (ft_strcmp(str, "des") == 0 || ft_strcmp(str, "des-cbc") == 0)
		ft_des_cbc(argv);
	else if (ft_strcmp(str, "des3") == 0 || ft_strcmp(str, "des3-cbc") == 0)
		ft_des3(argv);
	else if (ft_strcmp(str, "des3-ecb") == 0)
		ft_des_ecb(argv, 48);
	else
		return (0);
	return (1);
}

void	ft_er(char *str)
{
	write(1, "ft_ssl: Error: '", 16);
	write(1, str, ft_strlen(str));
	write(1, "' is an invalid command.\n\nStandard commands:\n\n", 50);
	write(1, "Message Digest commands:\n\nCipher commands:\n", 47);
	write(1, "base64\ndes\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n", 31);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (check(argv[1], argv) != 1)
			ft_er(argv[1]);
	}
	else
		write(1, "usage: ft_ssl command [command opts] [command args]\n", 53);
	return (0);
}
