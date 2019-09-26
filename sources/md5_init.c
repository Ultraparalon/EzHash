/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 21:46:45 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/06 21:46:47 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "md5.h"

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
	UINT	i;

	ret = (UCHAR *)ft_memalloc(sizeof(UCHAR) * (len + 8));
	ft_memcpy(ret, str, len);
	free(str);
	i = -1;
	while (++i < 8)
		ret[len++] = (UCHAR)(len_bit >> i * 8);
	return (ret);
}

static UINT		*get_hash(t_md *md, UCHAR *str)
{
	ULLI len_bit;

	len_bit = md->len << 3;
	str = add_uchar(str, md->len++, 128);
	while ((md->len & 63) != 56)
		str = add_uchar(str, md->len++, 0);
	str = add_len(str, md->len, len_bit);
	md->len = (md->len + 8) >> 2;
	return ((UINT *)str);
}

void			md5_init(t_md *md, char *source)
{
	md->state[0] = 0x67452301;
	md->state[1] = 0xefcdab89;
	md->state[2] = 0x98badcfe;
	md->state[3] = 0x10325476;
	md->hash = get_hash(md, (UCHAR *)source);
}
