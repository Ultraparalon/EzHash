/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:10:14 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 22:10:15 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512_224.h"
#include "ssl.h"

char	*sha512_224(char *source, const int len)
{
	t_sha	sh;
	char	*ret;

	sh.len = len;
	sha512_224_init(&sh, source);
	sha512_224_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes_512((UCHAR *)sh.state, 8);
	ret = hash_to_string_512(sh.state, 4);
	ret[56] = 0;
	return (ret);
}
