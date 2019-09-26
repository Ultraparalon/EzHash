/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:38:33 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 16:38:34 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha224.h"

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

void			sha224_init(t_sha *sh, char *source)
{
	sh->state[0] = 0xC1059ED8;
	sh->state[1] = 0x367CD507;
	sh->state[2] = 0x3070DD17;
	sh->state[3] = 0xF70E5939;
	sh->state[4] = 0xFFC00B31;
	sh->state[5] = 0x68581511;
	sh->state[6] = 0x64F98FA7;
	sh->state[7] = 0xBEFA4FA4;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
