/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:51:13 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/03 17:51:14 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ssl.h"

static void	create_hash(t_md *md)
{
	UINT i;

	i = 0;
	while (i < md->len)
	{
		md5_transform(md->state, &md->hash[i]);
		i += 16;
	}
}

char		*md5(char *source, const int len)
{
	t_md	md;

	md.len = len;
	md5_init(&md, source);
	create_hash(&md);
	free(md.hash);
	return (hash_to_string(md.state, 4));
}
