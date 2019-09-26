/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:38:53 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 16:38:54 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"

static void	init_buff(UINT *buff, const UINT *src)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		*buff++ = *src++;
	}
}

static void	init_data(UINT *data, const UINT *hash)
{
	UINT j;

	j = 0;
	while (j++ < 16)
	{
		*data++ = *hash++;
	}
	while (j++ < 65)
	{
		*data = *(data - 16) + S0(*(data - 15)) + *(data - 7) + S1(*(data - 2));
		data++;
	}
}

static void	sha224_transform(UINT *buff, const UINT *data)
{
	UINT	t[6];
	int		i;

	i = -1;
	while (++i < 64)
	{
		t[0] = ROTR(buff[0], 2) ^ ROTR(buff[0], 13) ^ ROTR(buff[0], 22);
		t[1] = (buff[0] & buff[1]) ^ (buff[0] & buff[2]) ^ (buff[1] & buff[2]);
		t[2] = t[0] + t[1];
		t[3] = ROTR(buff[4], 6) ^ ROTR(buff[4], 11) ^ ROTR(buff[4], 25);
		t[4] = (buff[4] & buff[5]) ^ ((~buff[4]) & buff[6]);
		t[5] = buff[7] + t[3] + t[4] + g_k[i] + data[i];
		buff[7] = buff[6];
		buff[6] = buff[5];
		buff[5] = buff[4];
		buff[4] = buff[3] + t[5];
		buff[3] = buff[2];
		buff[2] = buff[1];
		buff[1] = buff[0];
		buff[0] = t[5] + t[2];
	}
}

static void	add_hash(UINT *hash, const UINT *buff)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		*hash++ += *buff++;
	}
}

void		sha224_create_hash(t_sha *sh)
{
	UINT i;
	UINT data[64];
	UINT buff[8];

	i = 0;
	while (i < sh->len)
	{
		init_buff(buff, sh->state);
		init_data(data, &sh->hash[i]);
		sha224_transform(buff, data);
		add_hash(sh->state, buff);
		i += 16;
	}
}
