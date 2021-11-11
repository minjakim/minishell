/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:30:50 by snpark            #+#    #+#             */
/*   Updated: 2021/11/11 15:46:58 by snpark           ###   ########.fr       */
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
	print_export_list(t_hash *ex_list)
{
	while (ex_list)
	{
		printf("declare -x %s", ex_list->key);
		if (ex_list->value != NULL)
			printf("=\"%s\"", ex_list->value);
		printf("\n");
		ex_list = ex_list->next;
	}
}

int
	ms_export(char **argv, char **envp, t_io stream, t_hash **ex_list)
{
	t_key_value_idx	idx;
	int				offset;
	int				i;
	t_hash			*ex_handle;

	(void)stream;
	if (argv == NULL)
		exit(1);
	if (argv[1] == NULL)
	{
		print_export_list(*ex_list);
		return (1);
	}
	offset = find_offset(argv[1]);
	if (offset != -1)
		argv[1][offset] = '\0';
	if (legal_identifier(argv[1]) == 0)
	{
		write(2, "bash: ", 6);
		write(2, "export: `", 8);
		write(2, argv[1], strlen(argv[1]));
		write(2, "': is not a valid identifier\n", 29);
		argv[1][offset] = '=';
		exit(1);
	}
	ex_handle = *ex_list;
	while (ex_handle && strcmp(ex_handle->key, argv[1]) != 0)
		ex_handle = ex_handle->next;
//	if (ex_handle == NULL)
//	{
//		ex_handle = malloc(sizeof(t_hash));
//		if (ex_handle == NULL)
//			exit(1);
//		*ex_list = ex_handle;
//		memset(ex_handle, 0, sizeof(t_hash));
//	}
	if (ex_handle == NULL)
	{
		if (offset != -1)
			argv[1][offset] = '=';
		add_export_list(argv[1], ex_list);
	}
	else if (strcmp(argv[1], ex_handle->key) == 0 && offset != -1)
	{
		if (ex_handle->value != NULL)
			free(ex_handle->value);
		ex_handle->value = strdup(argv[1] + offset + 1);
	}
	idx = ms_getenv(argv[1], envp);
	argv[1][offset] = '=';
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
