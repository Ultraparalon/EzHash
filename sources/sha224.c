/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:38:11 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 16:38:14 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"
#include "ssl.h"

char	*sha224(char *source, const int len)
{
	t_sha	sh;

	sh.len = len;
	sha224_init(&sh, source);
	sha224_create_hash(&sh);
	free(sh.hash);
	ssl_rev_bytes((UCHAR *)sh.state, 8);
	return (hash_to_string(sh.state, 7));
}
