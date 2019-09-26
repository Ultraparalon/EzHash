/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:31:30 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/07 13:31:32 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha256.h"

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

static UINT		*get_hash(t_sha *sh, UCHAR *str)
{
	ULLI len_bit;

	len_bit = sh->len << 3;
	str = add_uchar(str, sh->len++, 128);
	while ((sh->len & 63) != 56)
		str = add_uchar(str, sh->len++, 0);
	str = add_len(str, sh->len, len_bit);
	sh->len = (sh->len + 8) >> 2;
	ssl_rev_bytes(str, sh->len);
	return ((UINT *)str);
}

void			sha256_init(t_sha *sh, char *source)
{
	sh->state[0] = 0x6A09E667;
	sh->state[1] = 0xBB67AE85;
	sh->state[2] = 0x3C6EF372;
	sh->state[3] = 0xA54FF53A;
	sh->state[4] = 0x510E527F;
	sh->state[5] = 0x9B05688C;
	sh->state[6] = 0x1F83D9AB;
	sh->state[7] = 0x5BE0CD19;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
