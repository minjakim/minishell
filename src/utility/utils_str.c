/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:25:11 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 17:31:58 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char
	*ft_strchr(const char *s, int c)
{
	unsigned char	var_c;
	char			*var_s;

	var_c = c;
	var_s = (char *)s;
	while (*var_s != var_c)
		if (!*var_s++)
			return (NULL);
	return (var_s);
}

int
	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
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
	const	char			*p;
	const	unsigned long	*lp;
	size_t					len;

	if (!s || !*(p = s))
		return (0);
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
			if ((len = test_byte(p, s)))
				return (len);
		}
		++lp;
	}
}

void
	ft_strmove(char *dest, char *src, int len)
{
	if (len < 0)
		return ;
	while(len--)
		*dest++ = *src++;
	*dest = *src;
}

