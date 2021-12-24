/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_etc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:10:32 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/24 15:14:40 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline int
	get_len(size_t x)
{
	if (x >= 1000000000)
		return (10);
	if (x >= 100000000)
		return (9);
	if (x >= 10000000)
		return (8);
	if (x >= 1000000)
		return (7);
	if (x >= 100000)
		return (6);
	if (x >= 10000)
		return (5);
	if (x >= 1000)
		return (4);
	if (x >= 100)
		return (3);
	if (x >= 10)
		return (2);
	return (1);
}

char
	*ft_itoa(int n)
{
	size_t		len;
	size_t		i;
	char		*res;

	if (n < 0)
		i = (size_t)(-n);
	else
		i = (size_t)n;
	len = get_len(i) + 1;
	if (n < 0)
		++len;
	res = (char *)xcalloc(len);
	if (!i)
		res[--len] = '0';
	while (i)
	{
		res[--len] = '0' + (i % 10);
		i /= 10;
	}
	if (len)
		res[--len] = '-';
	return (res);
}

static inline unsigned char
	convert(unsigned char *const c, const char *const str)
{
	return (*c = *str - '0');
}

int
	ft_shlvltoi(const char *str)
{
	int				i;
	unsigned char	a;

	i = 0;
	while (*str && convert(&a, str) < 10)
	{
		i = (i << 1) + (i << 3) + a;
		++str;
	}
	if (*str)
		return (FAILURE);
	return (i);
}
