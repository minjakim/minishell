/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 07:42:54 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	legal_number(const char *str)
{
	unsigned long long		n;
	int						negative;

	while ((*str >= 9 && *str <= 13) || *str == 0x20)
		++str;
	negative = 0;
	if (*str == '+' || *str == '-')
	{
		negative = (*str == '-');
		++str;
	}
	n = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((negative && n * 10 + *str - '0' > \
					(unsigned long long)LLONG_MAX + 1) \
				|| (!negative && n * 10 + *str - '0' > LLONG_MAX))
			return (0);
		n *= 10;
		n += *str - '0';
		++str;
	}
	if (*str)
		return (0);
	return (1);
}

int
	legal_variable_starter(const char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int
	legal_variable_char(const char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'));
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
	int				indx;

	c = string[0];
	indx = 0;
	if (legal_variable_starter (c) == 0)
		return (0);
	while (string[indx])
	{
		c = string[indx];
		if (c == '=')
			return (indx);
		if (c == '+' && string[indx + 1] == '=')
			return (indx + 1);
		if (legal_variable_char (c) == 0)
			return (0);
		indx++;
	}
	return (0);
}
