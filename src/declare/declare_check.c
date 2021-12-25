/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/25 14:38:56 by minjakim         ###   ########.fr       */
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

static inline void
	declare_type_check(const char *str, t_dc *dc)
{
	if (str[dc->i] == '=')
	{
		if (str[dc->i + 1] == '\0')
			dc->type = E_ONLY;
		if (str[dc->i + 1] != '\0')
			dc->type = EXPORT;
	}
	else if (str[dc->i] == '+')
	{
		if (str[dc->i + 1] == '=' && str[dc->i + 2] == '\0')
			dc->type = C_ONLY;
		else if (str[dc->i + 1] == '=' && str[dc->i + 2] != '\0')
			dc->type = CAT;
	}
}

t_dc
	declare_legal_check(const char *str)
{
	t_dc	dc;

	dc.i = 0;
	dc.type = EXCEPTION;
	if (!legal_variable_starter(str[dc.i]))
		return (dc);
	dc.type = K_ONLY;
	while (str[++dc.i])
	{
		declare_type_check(str, &dc);
		if (dc.type != K_ONLY)
			break ;
		if (!legal_variable_char(str[dc.i]))
		{
			dc.type = EXCEPTION;
			break ;
		}
	}
	return (dc);
}
