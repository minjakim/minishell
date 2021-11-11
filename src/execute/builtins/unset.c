/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:56:17 by snpark            #+#    #+#             */
/*   Updated: 2021/11/11 15:48:19 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	legal_variable_starter(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int
	legal_identifier(char *name)
{
	int	i;

	if (!name || !*name || legal_variable_starter(*name) == 0)
		return (0);
	i = 0;
	while (name[++i] != '\0')
		if (legal_variable_starter(name[i]) == 0)
			return (0);
	return (1);
}

int
	ms_unset(char **argv, char **envp, t_hash **ex_list)
{
	t_key_value_idx	idx;
	int				last_i;
	t_hash			*ex_handle;

	if (argv == NULL || argv[1] == NULL)
		return (1);
	if (legal_identifier(argv[1]) == 0)
	{
		write(2, "bash: ", 6);
		write(2, "unset: `", 8);
		write(2, argv[1], strlen(argv[1]));
		write(2, "': not a valid identifier\n", 26);
		exit(1);
	}
	ex_handle = *ex_list;
	while (ex_handle && strcmp(ex_handle->key, argv[1]) != 0)
		ex_handle = ex_handle->next;
	if (ex_handle && strcmp(ex_handle->key, argv[1]) == 0)
	{
		if (ex_handle->prev == NULL)
		{
			*ex_list = ex_handle->next;
			ex_handle->next->prev = NULL;
		}
		else
		{
			ex_handle->prev->next = ex_handle->next;
			ex_handle->next->prev = ex_handle->prev;
		}
		free(ex_handle->key);
		if (ex_handle->value)
			free(ex_handle->value);
		free(ex_handle);
	}
	last_i = -1;
	while (envp[++last_i] != NULL)
		;
	idx = ms_getenv(argv[1], envp);
	if (idx.key != -1)
	{
		free (envp[idx.key]);
		envp[idx.key] = envp[last_i];
		envp[last_i] = NULL;
	}
	return (1);
}

/*
**쉘 변수도 unset가능
**인자에 '='이 들어가면 에러
**bash: unset: 'argv[1]': is not a valid identifier
*/
