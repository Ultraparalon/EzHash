/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:49:57 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 17:49:58 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha512.h"

static UCHAR	*add_uchar(UCHAR *str, const UINT len, const UCHAR c)
{
	UCHAR *ret;

	ret = (UCHAR *)ft_memalloc(sizeof(UCHAR) * (len + 1));
	ft_memcpy(ret, str, len);
	ret[len] = c;
	free(str);
	return (ret);
}

static UCHAR	*add_len(UCHAR *str, UINT len, const ULLI len_bit)
{
	UCHAR	*ret;
	int		i;

	ret = (UCHAR *)ft_memalloc(sizeof(UCHAR) * (len + 8));
	ft_memcpy(ret, str, len);
	free(str);
	i = 7;
	while (i >= 0)
	{
		ret[len++] = (UCHAR)(len_bit >> i * 8);
		i--;
	}
	return (ret);
}

static ULINT	*get_hash(t_sha *sh, UCHAR *str)
{
	unsigned long long int len_bit;

	len_bit = sh->len << 3;
	str = add_uchar(str, sh->len++, 128);
	while ((sh->len & 127) != 120)
		str = add_uchar(str, sh->len++, 0);
	str = add_len(str, sh->len, len_bit);
	sh->len = (sh->len + 8) >> 3;
	ssl_rev_bytes_512(str, sh->len);
	return ((ULINT *)str);
}

void			sha512_init(t_sha *sh, char *source)
{
	sh->state[0] = 0x6a09e667f3bcc908;
	sh->state[1] = 0xbb67ae8584caa73b;
	sh->state[2] = 0x3c6ef372fe94f82b;
	sh->state[3] = 0xa54ff53a5f1d36f1;
	sh->state[4] = 0x510e527fade682d1;
	sh->state[5] = 0x9b05688c2b3e6c1f;
	sh->state[6] = 0x1f83d9abfb41bd6b;
	sh->state[7] = 0x5be0cd19137e2179;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
