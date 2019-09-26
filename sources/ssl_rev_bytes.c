/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_rev_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:11:19 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/11 13:11:23 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	ssl_rev_bytes(unsigned char *str, unsigned int len)
{
	unsigned char	buff[4];

	while (len--)
	{
		buff[3] = str[0];
		buff[2] = str[1];
		buff[1] = str[2];
		buff[0] = str[3];
		ft_memcpy(str, buff, 4);
		str += 4;
	}
}

void	ssl_rev_bytes_512(unsigned char *str, unsigned int len)
{
	unsigned char	buff[8];

	while (len--)
	{
		buff[7] = str[0];
		buff[6] = str[1];
		buff[5] = str[2];
		buff[4] = str[3];
		buff[3] = str[4];
		buff[2] = str[5];
		buff[1] = str[6];
		buff[0] = str[7];
		ft_memcpy(str, buff, 8);
		str += 8;
	}
}
