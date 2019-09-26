/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:49:41 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 17:49:42 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"
#include "ssl.h"

char	*sha512(char *source, const int len)
{
	t_sha	sh;

	sh.len = len;
	sha512_init(&sh, source);
	sha512_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes_512((UCHAR *)sh.state, 8);
	return (hash_to_string_512(sh.state, 8));
}
