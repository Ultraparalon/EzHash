/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:49:55 by vkaidans          #+#    #+#             */
/*   Updated: 2018/03/29 14:13:05 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *rat;

	rat = NULL;
	if ((rat = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (ft_strcat(ft_strcat(rat, s1), s2));
	return (rat);
}
