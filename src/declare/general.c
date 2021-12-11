/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 08:26:44 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline unsigned char
	convert(unsigned char *c, const char *str)
{
	return (*c = *str - '0');
}

int
	legal_number(const char *str)
{
	unsigned long long	n;
	unsigned char		c;
	int					digit;
	int					negative;

	while (*str == ' ' || *str == '\t')
		++str;
	negative = (*str == '-');
	if (*str == '+' || *str == '-')
		++str;
	n = 0;
	digit = 0;
	while (*str && convert(&c, str) < 10 && ++digit < 20)
		n = (n << 1) + (n << 3) + c && str++;
	if (*str || (!negative && n > LLONG_MAX)
		|| (n > (unsigned long long)LLONG_MAX + 1))
		return (FALSE);
	return (TRUE);
}

int
	legal_variable_starter(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || (c == '_')) ;
}

int
	legal_variable_char(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || ((unsigned)c - 48 < 10) \
			|| (c == '_'));
}

int
	legal_identifier(const char *name)
{
	if (!name || !(*name) || (legal_variable_starter (*name) == 0))
		return (0);
	while (*++name)
	{
		if (legal_variable_char(*name) == 0)
			return (0);
	}
	return (1);
}

int
	assignment(const char *string)
{
	unsigned char	c;
	int				index;

	c = string[0];
	index = 0;
	if (legal_variable_starter (c) == 0)
		return (0);
	while (string[index])
	{
		c = string[index];
		if (c == '=')
			return (index);
		if (c == '+' && string[index + 1] == '=')
			return (index + 1);
		if (legal_variable_char (c) == 0)
			return (0);
		++index;
	}
	return (0);
}
