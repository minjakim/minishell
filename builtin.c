/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:08 by snpark            #+#    #+#             */
/*   Updated: 2021/09/17 21:57:31 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_list;

int
	env(t_env *list)
{
	while (list != NULL)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}

int
	pwd()
{
	char cwd_buffer[4096];

	getcwd(cwd_buffer, 4096);
	printf("%s\n", cwd_buffer);
	return (0);
}

int
	echo(char *str, char flag)
{
	printf("%s%c", str, flag);
	return (0);
}

int
	cd(char *path)
{
	return (chdir(path));
}

int
	unset(const char *key)
{
	t_env	*tmp;
	t_env	*pre;

	tmp = env_list;
	pre = NULL;
	while (tmp && strcmp(tmp->key, key) && tmp->next)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	if (tmp && !strcmp(tmp->key, key))
	{
		free(tmp->key);
		free(tmp->value);
		pre->next = tmp->next;
		free(tmp);
	}
	return (0);
}
