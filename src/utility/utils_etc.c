/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_etc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:10:32 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/24 22:16:26 by minjakim         ###   ########.fr       */
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
	*ft_itoshlvl(int n)
{
	size_t		len;
	size_t		i;
	char		*shlvl;

	i = (size_t)n;
	len = get_len(i);
	shlvl = (char *)xcalloc(len);
	while (i)
	{
		shlvl[--len] = '0' + (i % 10);
		i /= 10;
	}
	return (shlvl);
}

static inline unsigned char
	convert(unsigned char *const c, const char *const str)
{
	return (*c = *str - '0');
}

int
	ft_shlvltoi(const char *str)
{
	unsigned char	shlvl;
	int				i;

	i = 0;
	while (*str && convert(&shlvl, str) < 10)
	{
		i = (i << 1) + (i << 3) + shlvl;
		++str;
	}
	if (*str)
		return (INIT_SHLVL);
	return (++i);
}
