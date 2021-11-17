/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:56:17 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:29:10 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	legal_variable_starter(char c) {
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int
	legal_identifier(const char *cmd, char *name)
{
	int	i;

	if (!name || !*name || legal_variable_starter(*name) == 0)
		return (0);
	i = 0;
	while (name[++i] != '\0')
	{
		if (legal_variable_starter(name[i]) == 0)
		{
			write(2, "bash: ", 6);
			write(2, cmd, strlen(cmd)); 
			write(2, ": `", 3);
			write(2, name, strlen(name));
			write(2, "': not a valid identifier\n", 26);
			return (0);
		}
	}
	return (1);
}

int
	delete_export_variable(char **argv, t_hash **ex_list)
{
	t_hash			*ex_handle;
	
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
	return (0);
}

int
	delete_env_variable(char **argv, char **envp)
{
	t_key_value_idx	idx;
	int				last_i;

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
	return (0);
}

int
	ms_unset(char **argv, char **envp, t_hash **ex_list, int *exit_status)
{

	if (argv == NULL || argv[1] == NULL)
	{
		*exit_status = 0;
		return (1);
	}
	if (legal_identifier("unset", argv[1]) == 0)
	{
		*exit_status = 1;
		return (1);
	}
	delete_export_variable(argv, ex_list);
	delete_env_variable(argv, envp);
	*exit_status = 0;
	return (1);
}

/*
**쉘 변수도 unset가능
**인자에 '='이 들어가면 에러
**bash: unset: 'argv[1]': is not a valid identifier
*/
