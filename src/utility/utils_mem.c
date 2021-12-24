/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:38:12 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/24 14:39:15 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline void
	loop(t_op *dstpp, t_op c, size_t len, size_t xlen)
{
	const t_op	step = 8 * OPSIZ;

	while (len)
	{
		((t_op *)*dstpp)[0] = c;
		((t_op *)*dstpp)[1] = c;
		((t_op *)*dstpp)[2] = c;
		((t_op *)*dstpp)[3] = c;
		((t_op *)*dstpp)[4] = c;
		((t_op *)*dstpp)[5] = c;
		((t_op *)*dstpp)[6] = c;
		((t_op *)*dstpp)[7] = c;
		*dstpp += step;
		--len;
	}
	while (xlen)
	{
		*(t_op *)*dstpp = c;
		*dstpp += OPSIZ;
		--xlen;
	}
}

void
	*ft_memset(void *s, int c, size_t n)
{
	t_op	dstp;
	t_op	cccc;

	dstp = (t_op)s;
	if (n >= 8)
	{
		cccc = (t_byte)c;
		cccc |= cccc << 8;
		cccc |= cccc << 16;
		cccc |= cccc << 32;
		loop(&dstp, cccc, n / (OPSIZ * 8), (n % (OPSIZ * 8)) / OPSIZ);
		n %= OPSIZ;
	}
	while (n--)
		*(t_byte *)dstp++ = c;
	return (s);
}

static void
	wordcpy(t_op dstp, t_op srcp, size_t n)
{
	t_op	a0;
	t_op	a1;

	if (n & 1)
	{
		((t_op *)dstp)[0] = ((t_op *)srcp)[0];
		if (n == 1)
			return ;
		srcp += OPSIZ;
		dstp += OPSIZ;
		--n;
	}
	while (n)
	{
		a0 = ((t_op *)srcp)[0];
		a1 = ((t_op *)srcp)[1];
		((t_op *)dstp)[0] = a0;
		((t_op *)dstp)[1] = a1;
		srcp += 16;
		dstp += 16;
		n -= 2;
	}
}

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_op	dstp;
	t_op	srcp;
	t_byte	*dstd;
	t_byte	*srcd;

	dstp = (t_op)dst;
	srcp = (t_op)src;
	if (dst == src)
		return (NULL);
	if (n >= 16)
	{
		wordcpy(dstp, srcp, n >> 3);
		srcp += n & -OPSIZ;
		dstp += n & -OPSIZ;
		n %= OPSIZ;
	}
	dstd = (t_byte *)dstp;
	srcd = (t_byte *)srcp;
	while (n--)
		*dstd++ = *srcd++;
	return (dst);
}
