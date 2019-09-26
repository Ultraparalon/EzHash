/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:11:02 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/10 22:11:04 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512_224.h"

static void	init_buff(ULINT *buff, const ULINT *src)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		*buff++ = *src++;
	}
}

static void	init_data(ULINT *data, const ULINT *hash)
{
	UINT j;

	j = 0;
	while (j++ < 16)
	{
		*data++ = *hash++;
	}
	while (j++ < 81)
	{
		*data = *(data - 16) + S0(*(data - 15)) + *(data - 7) + S1(*(data - 2));
		data++;
	}
}

static void	sha512_transform(ULINT *buff, const ULINT *data)
{
	ULINT	t[6];
	int		i;

	i = -1;
	while (++i < 80)
	{
		t[0] = ROTR(buff[0], 28) ^ ROTR(buff[0], 34) ^ ROTR(buff[0], 39);
		t[1] = (buff[0] & buff[1]) ^ (buff[0] & buff[2]) ^ (buff[1] & buff[2]);
		t[2] = t[0] + t[1];
		t[3] = ROTR(buff[4], 14) ^ ROTR(buff[4], 18) ^ ROTR(buff[4], 41);
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

static void	add_hash(ULINT *hash, const ULINT *buff)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		*hash++ += *buff++;
	}
}

void		sha512_224_create_hash(t_sha *sh)
{
	UINT	i;
	ULINT	data[80];
	ULINT	buff[8];

	i = 0;
	while (i < sh->len)
	{
		init_buff(buff, sh->state);
		init_data(data, &sh->hash[i]);
		sha512_transform(buff, data);
		add_hash(sh->state, buff);
		i += 16;
	}
}
