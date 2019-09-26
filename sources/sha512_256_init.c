/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:10:29 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 22:10:33 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha512_256.h"

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

void			sha512_256_init(t_sha *sh, char *source)
{
	sh->state[0] = 0x22312194FC2BF72C;
	sh->state[1] = 0x9F555FA3C84C64C2;
	sh->state[2] = 0x2393B86B6F53B151;
	sh->state[3] = 0x963877195940EABD;
	sh->state[4] = 0x96283EE2A88EFFE3;
	sh->state[5] = 0xBE5E1E2553863992;
	sh->state[6] = 0x2B0199FC2C85B8AA;
	sh->state[7] = 0x0EB72DDC81C52CA2;
	sh->hash = get_hash(sh, (UCHAR *)source);
}
