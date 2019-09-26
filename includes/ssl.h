/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:12:58 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/03 17:13:00 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# define FUNCS 7
# define FUNC(str, len) core->func->func(str, len)
# define ARGV core->argv
# define STAT core->status
# define NAME core->func->name
# define USAGE "usage: [type] [-pqr] [-s string] [files ...]"

# define ULLI unsigned long long int

# include <fcntl.h>
# include "libft.h"
// # include "/libraries/libft/includes/libft.h"

typedef struct	s_cypher
{
	char		name[10];
	char		*(*func)(char *, const int);
}				t_cypher;

typedef struct	s_core
{
	char		status;
	char		**argv;
	t_cypher	*func;
}				t_core;

void			wizzard(char **const argv);
char			*hash_to_string(unsigned int *hash, unsigned int size);
char			*hash_to_string_512(ULLI *hash, unsigned int size);
char			*md5(char *source, const int len);
char			*sha256(char *source, const int len);
char			*sha224(char *source, const int len);
char			*sha512(char *source, const int len);
char			*sha384(char *source, const int len);
char			*sha512_256(char *source, const int len);
char			*sha512_224(char *source, const int len);
void			ssl_rev_bytes(unsigned char *str, unsigned int len);
void			ssl_rev_bytes_512(unsigned char *str, unsigned int len);
void			ssl_reader(t_core *const core);
void			ssl_reader_in(const t_core *const core);

static t_cypher	g_cypher[FUNCS] =
{
	{ "md5", md5 },
	{ "sha256", sha256 },
	{ "sha224", sha224 },
	{ "sha512", sha512 },
	{ "sha384", sha384 },
	{ "sha512/256", sha512_256 },
	{ "sha512/224", sha512_224 }
};

#endif
