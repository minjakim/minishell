/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:25:11 by snpark            #+#    #+#             */
/*   Updated: 2021/12/24 22:05:27 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (!*s1++)
			return (OK);
	return ((unsigned char)*s1 - (unsigned char)*(--s2));
}

static long
	find(const t_byte *s, int c, long *chr)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (s[i] == c)
			return (*chr = (long)s + i);
		else if (!s[i])
			return (*chr = 0);
	}
	return (*chr = -1);
}

char
	*ft_strchr(const char *s, int c)
{
	const t_byte	*s_ptr = (const t_byte *)s;
	const t_op		*lg_ptr;
	t_op			charmask;
	t_op			word;
	long			chr;

	while ((t_op)s_ptr & 0b111)
	{
		if (*s_ptr++ == c)
			return ((char *)(s_ptr - 1));
		else if (*(s_ptr - 1) == '\0')
			return (NULL);
	}
	lg_ptr = (const t_op *)s_ptr;
	charmask = c | (c << 8);
	charmask |= charmask << 16;
	charmask |= charmask << 32;
	while (LOOP)
	{
		word = *lg_ptr++;
		if (((word - LOMAGIC) & (~word) & HIMAGIC) || \
			(((word ^ charmask) - LOMAGIC) & ~(word ^ charmask) & HIMAGIC))
			if (find((const t_byte *)(lg_ptr - 1), c, &chr) != -1)
				return ((char *)chr);
	}
}

static inline size_t
	test_byte(const char *p, const char *s)
{
	if (!p[0])
		return (p - s);
	if (!p[1])
		return (p - s + 1);
	if (!p[2])
		return (p - s + 2);
	if (!p[3])
		return (p - s + 3);
	if (!p[4])
		return (p - s + 4);
	if (!p[5])
		return (p - s + 5);
	if (!p[6])
		return (p - s + 6);
	if (!p[7])
		return (p - s + 7);
	return (0);
}

size_t
	ft_strlen(const char *s)
{
	const char			*p;
	const unsigned long	*lp;
	size_t				len;

	if (!s || !*s)
		return (0);
	p = s;
	while ((unsigned long)p & (sizeof(long) - 1))
	{
		if (!*p)
			return (p - s);
		++p;
	}
	lp = (const unsigned long *)p;
	while (TRUE)
	{
		if ((*lp - LOMAGIC) & HIMAGIC)
		{
			p = (const char *)(lp);
			len = test_byte(p, s);
			if (len)
				return (len);
		}
		++lp;
	}
}
