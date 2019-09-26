/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_hash_to_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 21:36:56 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/06 21:36:57 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static void	block_to_string(char *str, unsigned int block)
{
	unsigned int x;

	x = 0;
	while (x++ != 4)
	{
		*str++ = "0123456789abcdef"[((block >> 4) & 0xf)];
		*str++ = "0123456789abcdef"[(block & 0xf)];
		block >>= 8;
	}
}

char		*hash_to_string(unsigned int *hash, unsigned int size)
{
	char			*str;
	unsigned int	i;

	i = -1;
	str = (char *)ft_memalloc(sizeof(char) * ((size << 3) + 1));
	while (++i < size)
	{
		block_to_string(&str[i << 3], hash[i]);
	}
	return (str);
}

static void	block_to_string_512(char *str, unsigned long long int block)
{
	unsigned int x;

	x = 0;
	while (x++ != 8)
	{
		*str++ = "0123456789abcdef"[((block >> 4) & 0xf)];
		*str++ = "0123456789abcdef"[(block & 0xf)];
		block >>= 8;
	}
}

char		*hash_to_string_512(unsigned long long int *hash, unsigned int size)
{
	char			*str;
	unsigned int	i;

	i = -1;
	str = (char *)ft_memalloc(sizeof(char) * ((size << 4) + 1));
	while (++i < size)
	{
		block_to_string_512(&str[i << 4], hash[i]);
	}
	return (str);
}
