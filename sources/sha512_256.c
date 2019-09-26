/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:10:07 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 22:10:09 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512_256.h"
#include "ssl.h"

char	*sha512_256(char *source, const int len)
{
	t_sha	sh;

	sh.len = len;
	sha512_256_init(&sh, source);
	sha512_256_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes_512((UCHAR *)sh.state, 8);
	return (hash_to_string_512(sh.state, 4));
}
