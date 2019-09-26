/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:37:25 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/03 16:37:26 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define FF(a, b, c, d, x, s, z) a = b + ROTATE_LEFT(a + F(b, c, d) + x + z, s)
# define GG(a, b, c, d, x, s, z) a = b + ROTATE_LEFT(a + G(b, c, d) + x + z, s)
# define HH(a, b, c, d, x, s, z) a = b + ROTATE_LEFT(a + H(b, c, d) + x + z, s)
# define II(a, b, c, d, x, s, z) a = b + ROTATE_LEFT(a + I(b, c, d) + x + z, s)

# define A buff[0]
# define B buff[1]
# define C buff[2]
# define D buff[3]

# define UCHAR unsigned char
# define UINT unsigned int
# define ULLI unsigned long long int

typedef struct		s_md
{
	UINT			len;
	UINT			*hash;
	UINT			state[4];
}					t_md;

void				md5_transform(UINT *state, const UINT *x);
void				md5_init(t_md *md, char *source);

#endif
