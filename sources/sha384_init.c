/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:47:35 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 21:47:36 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha384.h"

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
	ULLI len_bit;

	len_bit = sh->len << 3;
	str = add_uchar(str, sh->len++, 128);
	while ((sh->len & 127) != 120)
		str = add_uchar(str, sh->len++, 0);
	str = add_len(str, sh->len, len_bit);
	sh->len = (sh->len + 8) >> 3;
	ssl_rev_bytes_512(str, sh->len);
	return ((ULINT *)str);
}

void			sha384_init(t_sha *sh, char *source)
{
	sh->state[0] = 0xCBBB9D5DC1059ED8;
	sh->state[1] = 0x629A292A367CD507;
	sh->state[2] = 0x9159015A3070DD17;
	sh->state[3] = 0x152FECD8F70E5939;
	sh->state[4] = 0x67332667FFC00B31;
	sh->state[5] = 0x8EB44A8768581511;
	sh->state[6] = 0xDB0C2E0D64F98FA7;
	sh->state[7] = 0x47B5481DBEFA4FA4;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
