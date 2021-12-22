/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 19:02:12 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	legal_variable_starter(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || (c == '_'));
}

int
	legal_variable_char(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || ((unsigned)c - '0' < 10) \
			|| (c == '_'));
}

int
	declare_legal_check(const char *str)
{
	int	index;

	index = 0;
	if (!legal_variable_starter(str[index]))
		return (FALSE);
	while (str[index])
	{
		if (str[index] == '=')
			return (index);
		if (str[index] == '+' && str[index + 1] == '=')
			return (index + 1);
		if (!legal_variable_char(str[index]))
			return (FALSE);
		++index;
	}
	return (TRUE);
}
