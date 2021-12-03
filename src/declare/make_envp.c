/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:39:06 by snpark            #+#    #+#             */
/*   Updated: 2021/12/02 22:03:56 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	free_envp(char **envp)
{
	int		i;

	i = -1;
	while(envp[++i])
		free(envp[i]);
	free(envp);
}

int
	envplen(t_hash *handle)
{
	int envp_len;

	envp_len = 0;
	while (handle)
	{
		if (handle->flag & H_EXPORT && !(handle->flag & H_KEYONLY))
			++envp_len;
		handle = handle->next;
	}
	return (envp_len);
}

int
	make_envp(char **new_envp, t_hash *handle)
{
	int	i;

	i = 0;
	while (handle)
	{
		if (handle->flag & H_EXPORT && !(handle->flag & H_KEYONLY))
		{
			new_envp[i] = malloc(sizeof(char)\
					* (strlen(handle->key) + strlen(handle->value)  + 2));
			if (new_envp[i] == NULL)
				return (1);
			strcat(strcat(strcpy(new_envp[i], handle->key), "="),\
					handle->value);
			++i;
		}
		handle = handle->next;
	}
	return (0);
}
