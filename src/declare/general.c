/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 16:38:54 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	legal_variable_starter(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int
	legal_variable_char(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
}

int
	legal_identifier (char *name)
{
	int				i;

	if (!name || !(*name) || (legal_variable_starter (*name) == 0))
	  return (0);
	i = 0;
	while (name[++i])
	{
		if (legal_variable_char(name[i]) == 0)
			return (0);
	}
	return (1);
}

int
	assignment (const char *string)
{
	unsigned char	c;
	int			indx;

	c = string[0];
	indx = 0;
	if (legal_variable_starter (c) == 0)
    	return (0);
	while (string[indx])
	{
		c = string[indx];
		if (c == '=')
			return (indx);
		if (c == '+' && string[indx+1] == '=')
			return (indx + 1);
		if (legal_variable_char (c) == 0)
			return (0);
      indx++;
    }
	return (0);
}

t_hash
	*check_declare_key(t_hash *head, char *key)
{
	t_hash	*back;
	t_hash	*handle;

	handle = head;
	back = handle;
	while (handle)
	{
		if (*key == *handle->key && strcmp(key, handle->key) == 0)
			return (back);
		if (strcmp(key, handle->key) < 0)
			return (back);
		back = handle;
		handle = handle->next;
	}
	return (back);
}

