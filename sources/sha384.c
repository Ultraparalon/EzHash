/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:40:55 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 21:40:56 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384.h"
#include "ssl.h"

char	*sha384(char *source, const int len)
{
	t_sha	sh;

	sh.len = len;
	sha384_init(&sh, source);
	sha384_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes_512((UCHAR *)sh.state, 8);
	return (hash_to_string_512(sh.state, 6));
}
