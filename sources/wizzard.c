/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wizzard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:03:07 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/03 17:03:09 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

/*
** ───────▄▀▀▀▀▀▀▀▀▀▀▄▄
** ────▄▀▀░░░░░░░░░░░░░▀▄
** ──▄▀░░░░░░░░░░░░░░░░░░▀▄
** ──█░░░░░░░░░░░░░░░░░░░░░▀▄
** ─▐▌░░░░░░░░▄▄▄▄▄▄▄░░░░░░░▐▌
** ─█░░░░░░░░░░░▄▄▄▄░░▀▀▀▀▀░░█
** ▐▌░░░░░░░▀▀▀▀░░░░░▀▀▀▀▀░░░▐▌
** █░░░░░░░░░▄▄▀▀▀▀▀░░░░▀▀▀▀▄░█
** █░░░░░░░░░░░░░░░░▀░░░▐░░░░░▐▌
** ▐▌░░░░░░░░░▐▀▀██▄░░░░░░▄▄▄░▐▌
** ─█░░░░░░░░░░░▀▀▀░░░░░░▀▀██░░█
** ─▐▌░░░░▄░░░░░░░░░░░░░▌░░░░░░█
** ──▐▌░░▐░░░░░░░░░░░░░░▀▄░░░░░█
** ───█░░░▌░░░░░░░░▐▀░░░░▄▀░░░▐▌
** ───▐▌░░▀▄░░░░░░░░▀░▀░▀▀░░░▄▀
** ───▐▌░░▐▀▄░░░░░░░░░░░░░░░░█
** ───▐▌░░░▌░▀▄░░░░▀▀▀▀▀▀░░░█
** ───█░░░▀░░░░▀▄░░░░░░░░░░▄▀
** ──▐▌░░░░░░░░░░▀▄░░░░░░▄▀
** ─▄▀░░░▄▀░░░░░░░░▀▀▀▀█▀
** ▀░░░▄▀░░░░░░░░░░▀░░░▀▀▀▀▄▄▄▄▄
*/

static t_cypher	*typer(const char *const type)
{
	int i;

	i = -1;
	while (type && ++i < FUNCS)
	{
		if (!ft_strcmp(type, g_cypher[i].name))
			return (&g_cypher[i]);
	}
	ft_error("no such hash type\n \
	types:	md5 sha224 sha256 sha384\n \
		sha512 sha512/256 sha512/224");
	return (NULL);
}

static void		ssl_reader_str(const t_core *const core, const char *const src)
{
	char *hash;

	if (!src)
	{
		ft_error(USAGE);
	}
	hash = FUNC(ft_strdup(src), ft_strlen(src));
	if (STAT & 0b1)
	{
		ft_printf("%s\n", hash);
	}
	else
	{
		(STAT & 0b10) ? ft_printf("%s \"%s\"\n", hash, src)
					: ft_printf("%s (\"%s\") = %s\n", NAME, src, hash);
	}
	free(hash);
}

static void		flag_check(t_core *const core, const char *str)
{
	while (*str)
	{
		if (*str == 'p')
		{
			STAT |= 0b100;
			ssl_reader_in(core);
		}
		else if (*str == 'q')
			STAT |= 0b1;
		else if (*str == 'r')
			STAT |= 0b10;
		else if (*str == 's')
		{
			STAT |= 0b100;
			ssl_reader_str(core, (*(str + 1)) ? ++str : *(++ARGV));
			break ;
		}
		else
			ft_error(USAGE);
		str++;
	}
}

static void		flager(t_core *const core)
{
	while (*ARGV && (*ARGV)[0] == '-' && (*ARGV)[1])
	{
		flag_check(core, (*ARGV) + 1);
		ARGV++;
	}
}

void			wizzard(char **const argv)
{
	t_core		core;

	core.argv = argv;
	core.status = 0;
	core.func = typer(*(core.argv)++);
	flager(&core);
	ssl_reader(&core);
}
