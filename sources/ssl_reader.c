/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:12:53 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/09 20:12:55 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

/*
** __________████████_____██████
** _________█░░░░░░░░██_██░░░░░░█
** ________█░░░░░░░░░░░█░░░░░░░░░█
** _______█░░░░░░░███░░░█░░░░░░░░░█
** _______█░░░░███░░░███░█░░░████░█
** ______█░░░██░░░░░░░░███░██░░░░██
** _____█░░░░░░░░░░░░░░░░░█░░░░░░░░███
** ____█░░░░░░░░░░░░░██████░░░░░████░░█
** ____█░░░░░░░░░█████░░░████░░██░░██░░█
** ___██░░░░░░░███░░░░░░░░░░█░░░░░░░░███
** __█░░░░░░░░░░░░░░█████████░░█████████
** _█░░░░░░░░░░█████_████___████_█████___█
** _█░░░░░░░░░░█______█_███__█_____███_█___█
** █░░░░░░░░░░░░█___████_████____██_██████
** ░░░░░░░░░░░░░█████████░░░████████░░░█
** ░░░░░░░░░░░░░░░░█░░░░░█░░░░░░░░░░░░█
** ░░░░░░░░░░░░░░░░░░░░██░░░░█░░░░░░██
** ░░░░░░░░░░░░░░░░░░██░░░░░░░███████
** ░░░░░░░░░░░░░░░░██░░░░░░░░░░█░░░░░█
** ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█
** ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█
** ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█
** ░░░░░░░░░░░█████████░░░░░░░░░░░░░░██
** ░░░░░░░░░░█▒▒▒▒▒▒▒▒███████████████▒▒█
** ░░░░░░░░░█▒▒███████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█
** ░░░░░░░░░█▒▒▒▒▒▒▒▒▒█████████████████
** ░░░░░░░░░░████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█
** ░░░░░░░░░░░░░░░░░░██████████████████
** ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█
** ██░░░░░░░░░░░░░░░░░░░░░░░░░░░██
** ▓██░░░░░░░░░░░░░░░░░░░░░░░░██
** ▓▓▓███░░░░░░░░░░░░░░░░░░░░█
** ▓▓▓▓▓▓███░░░░░░░░░░░░░░░██
** ▓▓▓▓▓▓▓▓▓███████████████▓▓█
** ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██
** ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█
** ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█
*/

static int	data_join(char **const cont, const char *const src,
							const int clen, const int slen)
{
	char *tmp;

	tmp = malloc(clen + slen + 1);
	*(tmp + clen + slen) = 0;
	ft_memcpy(tmp, *cont, clen);
	ft_memcpy((tmp + clen), src, slen);
	ft_strdel(cont);
	*cont = tmp;
	return (clen + slen);
}

static int	data_get(char **const container, const int input)
{
	char	buff[1024];
	int		len;
	int		flen;

	flen = 0;
	while ((len = read(input, buff, 1024)) > 0)
	{
		buff[len] = 0;
		flen = data_join(container, buff, flen, len);
	}
	return (flen);
}

static int	get_input(const char *const filename)
{
	int fd;

	if ((fd = open(filename, O_RDWR)) < 0)
	{
		ft_printf("error: no such file '%s'\n", filename);
	}
	return (fd);
}

void		ssl_reader_in(const t_core *const core)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = data_get(&tmp, 0);
	if (tmp && (STAT & 0b100))
	{
		ft_printf("%s", tmp);
	}
	tmp = FUNC(tmp, len);
	ft_printf("%s\n", tmp);
	ft_strdel(&tmp);
}

void		ssl_reader(t_core *const core)
{
	char	*hash;
	int		len;

	hash = NULL;
	if (!*ARGV && !(STAT & 0b100))
		ssl_reader_in(core);
	while (*ARGV)
	{
		if ((len = get_input(*ARGV)) > 0)
		{
			len = data_get(&hash, len);
			hash = FUNC(hash, len);
			if (STAT & 0b1)
				ft_printf("%s\n", hash);
			else
				(STAT & 0b10) ? ft_printf("%s %s\n", hash, *ARGV)
							: ft_printf("%s (%s) = %s\n", NAME, *ARGV, hash);
			ft_strdel(&hash);
		}
		ARGV++;
	}
}
