/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:49:10 by vkaidans          #+#    #+#             */
/*   Updated: 2019/02/04 17:49:12 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	md5_round_1(UINT *buff, const UINT *x)
{
	FF(A, B, C, D, x[0], 7, 0xd76aa478);
	FF(D, A, B, C, x[1], 12, 0xe8c7b756);
	FF(C, D, A, B, x[2], 17, 0x242070db);
	FF(B, C, D, A, x[3], 22, 0xc1bdceee);
	FF(A, B, C, D, x[4], 7, 0xf57c0faf);
	FF(D, A, B, C, x[5], 12, 0x4787c62a);
	FF(C, D, A, B, x[6], 17, 0xa8304613);
	FF(B, C, D, A, x[7], 22, 0xfd469501);
	FF(A, B, C, D, x[8], 7, 0x698098d8);
	FF(D, A, B, C, x[9], 12, 0x8b44f7af);
	FF(C, D, A, B, x[10], 17, 0xffff5bb1);
	FF(B, C, D, A, x[11], 22, 0x895cd7be);
	FF(A, B, C, D, x[12], 7, 0x6b901122);
	FF(D, A, B, C, x[13], 12, 0xfd987193);
	FF(C, D, A, B, x[14], 17, 0xa679438e);
	FF(B, C, D, A, x[15], 22, 0x49b40821);
}

static void	md5_round_2(UINT *buff, const UINT *x)
{
	GG(A, B, C, D, x[1], 5, 0xf61e2562);
	GG(D, A, B, C, x[6], 9, 0xc040b340);
	GG(C, D, A, B, x[11], 14, 0x265e5a51);
	GG(B, C, D, A, x[0], 20, 0xe9b6c7aa);
	GG(A, B, C, D, x[5], 5, 0xd62f105d);
	GG(D, A, B, C, x[10], 9, 0x2441453);
	GG(C, D, A, B, x[15], 14, 0xd8a1e681);
	GG(B, C, D, A, x[4], 20, 0xe7d3fbc8);
	GG(A, B, C, D, x[9], 5, 0x21e1cde6);
	GG(D, A, B, C, x[14], 9, 0xc33707d6);
	GG(C, D, A, B, x[3], 14, 0xf4d50d87);
	GG(B, C, D, A, x[8], 20, 0x455a14ed);
	GG(A, B, C, D, x[13], 5, 0xa9e3e905);
	GG(D, A, B, C, x[2], 9, 0xfcefa3f8);
	GG(C, D, A, B, x[7], 14, 0x676f02d9);
	GG(B, C, D, A, x[12], 20, 0x8d2a4c8a);
}

static void	md5_round_3(UINT *buff, const UINT *x)
{
	HH(A, B, C, D, x[5], 4, 0xfffa3942);
	HH(D, A, B, C, x[8], 11, 0x8771f681);
	HH(C, D, A, B, x[11], 16, 0x6d9d6122);
	HH(B, C, D, A, x[14], 23, 0xfde5380c);
	HH(A, B, C, D, x[1], 4, 0xa4beea44);
	HH(D, A, B, C, x[4], 11, 0x4bdecfa9);
	HH(C, D, A, B, x[7], 16, 0xf6bb4b60);
	HH(B, C, D, A, x[10], 23, 0xbebfbc70);
	HH(A, B, C, D, x[13], 4, 0x289b7ec6);
	HH(D, A, B, C, x[0], 11, 0xeaa127fa);
	HH(C, D, A, B, x[3], 16, 0xd4ef3085);
	HH(B, C, D, A, x[6], 23, 0x4881d05);
	HH(A, B, C, D, x[9], 4, 0xd9d4d039);
	HH(D, A, B, C, x[12], 11, 0xe6db99e5);
	HH(C, D, A, B, x[15], 16, 0x1fa27cf8);
	HH(B, C, D, A, x[2], 23, 0xc4ac5665);
}

static void	md5_round_4(UINT *buff, const UINT *x)
{
	II(A, B, C, D, x[0], 6, 0xf4292244);
	II(D, A, B, C, x[7], 10, 0x432aff97);
	II(C, D, A, B, x[14], 15, 0xab9423a7);
	II(B, C, D, A, x[5], 21, 0xfc93a039);
	II(A, B, C, D, x[12], 6, 0x655b59c3);
	II(D, A, B, C, x[3], 10, 0x8f0ccc92);
	II(C, D, A, B, x[10], 15, 0xffeff47d);
	II(B, C, D, A, x[1], 21, 0x85845dd1);
	II(A, B, C, D, x[8], 6, 0x6fa87e4f);
	II(D, A, B, C, x[15], 10, 0xfe2ce6e0);
	II(C, D, A, B, x[6], 15, 0xa3014314);
	II(B, C, D, A, x[13], 21, 0x4e0811a1);
	II(A, B, C, D, x[4], 6, 0xf7537e82);
	II(D, A, B, C, x[11], 10, 0xbd3af235);
	II(C, D, A, B, x[2], 15, 0x2ad7d2bb);
	II(B, C, D, A, x[9], 21, 0xeb86d391);
}

void		md5_transform(UINT *state, const UINT *x)
{
	UINT buff[4];

	A = state[0];
	B = state[1];
	C = state[2];
	D = state[3];
	md5_round_1(buff, x);
	md5_round_2(buff, x);
	md5_round_3(buff, x);
	md5_round_4(buff, x);
	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
}
