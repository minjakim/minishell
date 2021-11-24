/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:05:00 by snpark            #+#    #+#             */
/*   Updated: 2021/11/24 19:04:33 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	sort_export_list(t_hash *val, t_hash **list)
{
	t_hash	*handle;
	int		val_is_long;

	if (list == NULL)
		return ;//error
	if (*list == NULL)
		*list = val;
	else
	{
		handle = *list;
		while (handle != NULL)
		{
			val_is_long = strcmp(val->key, handle->key);
			if (val_is_long > 0 && handle->next == NULL)
			{
				handle->next = val;
				val->prev = handle;
				return ;
			}
			else if (val_is_long > 0)
				handle = handle->next;
			else if (val_is_long < 0)
			{
				if (handle->prev == NULL)
					*list = val;
				val->prev = handle->prev;
				if (handle->prev != NULL)
					handle->prev->next = val;
				val->next = handle;
				handle->prev = val;	
				return ;
			}
			if (val_is_long == 0)
			{
				free(handle->value);
				handle->value = val->value;
				free(val->key);
				free(val);
				return ;
			}
		}
	}
}

void
	add_export_list(char *str, t_hash **list)
{
	t_hash	*val;
	int		offset;

	if (str == NULL)
		return ;
	offset = find_offset(str);
	val = malloc(sizeof(t_hash));
	if (val == NULL)
		exit(1);
	memset((void *)val, '\0', sizeof(t_hash));
	if (str[offset] == '=')
	{
		val->value = strdup(str + offset + 1);
		str[offset] = '\0';
	}
	val->key = strdup(str);
	if (legal_identifier(NULL, val->key) == 0)
		;//error message;
	sort_export_list(val, list);
}

int
	parse_env(char ***original_envp, t_hash **export_list)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * ARG_MAX);
	i = -1;
	while ((*original_envp)[++i] != NULL)
	{
		//export_list에 하나씩 추가 자신이 들어갈 위치를 파악하면서
		add_export_list((*original_envp)[i], export_list);
		new_envp[i] = strdup((*original_envp)[i]);//replace strdup
		if (new_envp[i] == NULL)
			return (1);
	}
	new_envp[i] = NULL;
	*original_envp = new_envp;
	return (0);
}

/*
** Make char **env size ARG_MAX in limits.h
** fill last index NULL
*/
