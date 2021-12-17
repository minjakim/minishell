/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:10:32 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/17 19:54:29 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	temp_print_list(t_word_list *temp)
{
	while (temp)
	{
		printf("%s %d\n", temp->word.word, temp->word.flags);
		temp = temp->next;
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

	if (!*(p = s))
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
	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*var_b;
	unsigned char	var_c;

	var_b = b;
	var_c = c;
	while (len--)
		*var_b++ = var_c;
	return (b);
}

static void
	wordcpy(t_op dstp, t_op srcp, size_t n)
{
	t_op a0;
	t_op a1;

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

char
	*ft_strdup(const char *s1)
{
	void	*dst;
	size_t	n;

	n = ft_strlen(s1) + 1;
	dst = xmalloc(sizeof(char) * n);
	return (ft_memcpy(dst, s1, n));
}

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
    int    i;

    i = 0;
    while (s1[i] != '\0' && s1[i] == s2[i])
        ++i;
    return (s1[i] - s2[i]);
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
    *ft_strcat(char *s1, const char *s2)
{
    char *ptr;

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
	*ft_strndup(const char *s1, size_t n)
{
	char	*dst;

	if (!s1)
		return (NULL);
	dst = xmalloc(sizeof(char) * (n + 1));
	dst[n] = '\0';
	while (n--)
		dst[n] = s1[n];
	return (dst);
}

char
	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int		i;

	if (dst == NULL)
		return (NULL);
	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
