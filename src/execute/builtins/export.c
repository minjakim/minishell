/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:30:50 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:22:35 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	find_offset(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (-1);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
		return (i);
	return (-1);
}

void
	print_export_list(t_hash *ex_list, t_io stream)
{
	while (ex_list)
	{
		write(stream.out, "declare -x ", 11);
		write(stream.out, ex_list->key, strlen(ex_list->key));
		if (ex_list->value != NULL)
		{
			write(stream.out, "=\"", 2);
			write(stream.out, ex_list->value, strlen(ex_list->value));
			write(stream.out, "\"", 1);
		}
		write(stream.out, "\n", 1);
		ex_list = ex_list->next;
	}
}

int
	update_export_list(int offset, char **argv, int *exit_status, t_hash **ex_list)
{
	t_hash			*ex_handle;
	
	if (offset != -1)
		argv[1][offset] = '\0';
	if (legal_identifier("export", argv[1]) == 0)
	{
		*exit_status = 1;
		return (-1);
	}
	ex_handle = *ex_list;
	while (ex_handle && strcmp(ex_handle->key, argv[1]) != 0)
		ex_handle = ex_handle->next;
	if (ex_handle == NULL)/*매칭되는 키가 없을 경우 추가*/
	{
		if (offset != -1)
			argv[1][offset] = '=';
		add_export_list(argv[1], ex_list);
	}
	else if (strcmp(argv[1], ex_handle->key) == 0 && offset != -1)/*매칭되는 키가 있을 경우 밸류만 업데이트*/
	{
		if (ex_handle->value != NULL)
			free(ex_handle->value);
		ex_handle->value = strdup(argv[1] + offset + 1);
	}
	return (1);
}

int
	update_envp(char **argv, char **envp)
{
	t_key_value_idx	idx;
	int				i;

	idx = ms_getenv(argv[1], envp);
	if (idx.key == -1)
	{
		i = -1;
		while (envp[++i] != NULL)
			;
		if (i >= ARG_MAX)
			return (0);
		envp[i] = strdup(argv[1]);
		envp[i + 1] = NULL;
	}
	else
	{
		free(envp[idx.key]);
		envp[idx.key] = strdup(argv[1]);
	}
	return (1);
}

int
	ms_export(t_command cmd, char **envp, t_hash **ex_list, int *exit_status)
{
	int				offset;
	char			**argv;

	argv = cmd.argv;
	if (argv && argv[1] == NULL)
	{
		print_export_list(*ex_list, cmd.stream);
		*exit_status = 0;
		return (1);
	}
	offset = find_offset(argv[1]);
	if (update_export_list(offset, argv, exit_status, ex_list) == -1)
		return (1);
	update_envp(argv, envp);
	*exit_status = 0;
	return (1);
}
