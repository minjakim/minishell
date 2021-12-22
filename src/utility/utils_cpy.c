/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:28 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 17:31:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char
	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;

	if (!s2 || !*s2)
		return (s1);
	ptr = s1;
	while (*s1)
		++s1;
	while (*s2)
		*s1++ = *s2++;
	if (*s2 == '\0')
		*s1 = *s2;
	return (ptr);
}

char
	*ft_strcpy(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = *src;
	return (dst);
}

char
	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (dst == NULL)
		return (NULL);
	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	while (i < len)
		dst[i++] = '\0';
	return (dst);
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
