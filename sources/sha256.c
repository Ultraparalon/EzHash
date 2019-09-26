/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:31:11 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/07 13:31:12 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "ssl.h"

char	*sha256(char *source, const int len)
{
	t_sha	sh;

	sh.len = len;
	sha256_init(&sh, source);
	sha256_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes((UCHAR *)sh.state, 8);
	return (hash_to_string(sh.state, 8));
}
