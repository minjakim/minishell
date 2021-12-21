/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:51:01 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 20:55:24 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	declare_update_envp(void)
{
	const t_declare	*node = g_status.env.head;
	extern char		**environ;
	char			**envp;
	int				i;

	envp = xcalloc(sizeof(char *) * g_status.env.envc);
	i = -1;
	while (node)
	{
		if (node->exported)
		{
			envp[++i] = xcalloc((ft_strlen(node->key) + \
											ft_strlen(node->value) + 2));
			ft_strcat(ft_strcat(ft_strcpy(envp[i], node->key), "="), \
																node->value);
		}
		node = node->next;
	}
	environ = envp;
	dispose_argv(g_status.env.envp);
	g_status.env.envp = environ;
	return (SUCCESS);
}

int
	declare_unset(const char *str)
{
	return (SUCCESS);
}

t_declare
	*declare_new(const char *str)
{
	t_declare	*node;

	node = xcalloc(sizeof(t_declare));
	node->key = ft_strndup(str, ft_strchr(str, '=') - str);
	node->value = ft_strdup(ft_strchr(str, '=') + 1);
	return (node);
}

t_declare
	*declare_add(const char *str)
{
	g_status.env.tail->next = declare_new(str);
	g_status.env.tail = g_status.env.tail->next;
	return (g_status.env.tail);
}

int
	declare_init(void)
{
	extern char	**environ;
	char		**envp;

	envp = environ;
	g_status.env.envc = -1;
	if (envp[++g_status.env.envc])
	{
		g_status.env.head = declare_new(envp[++g_status.env.envc]);
		g_status.env.head->exported = TRUE;
		g_status.env.tail = g_status.env.head;
		while (envp[++g_status.env.envc])
			(declare_add(envp[g_status.env.envc]))->exported = TRUE;
	}
	g_status.env.envp = NULL;
	declare_update_envp();
	return (SUCCESS);
}
