/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:10:50 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 22:10:51 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha512_224.h"

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

void			sha512_224_init(t_sha *sh, char *source)
{
	sh->state[0] = 0x8C3D37C819544DA2;
	sh->state[1] = 0x73E1996689DCD4D6;
	sh->state[2] = 0x1DFAB7AE32FF9C82;
	sh->state[3] = 0x679DD514582F9FCF;
	sh->state[4] = 0x0F6D2B697BD44DA8;
	sh->state[5] = 0x77E36F7304C48942;
	sh->state[6] = 0x3F9D85A86A1D36C8;
	sh->state[7] = 0x1112E6AD91D692A1;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
