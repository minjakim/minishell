/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 20:56:13 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	declare_update_envp(void)
{
	const t_declare	*node = g_status.env.head;
	char			**envp;
	int				i;

	if (!g_status.env.edited)
		return ;
	envp = xcalloc(sizeof(char *) * g_status.env.envc + 1);
	i = -1;
	while (node)
	{
		if (node->key.str && node->value.str && node->line)
			envp[++i] = node->line;
		node = node->next;
	}
	xfree(g_status.env.envp);
	g_status.env.envp = envp;
	g_status.env.edited = FALSE;
}

static int
	print_env(const char *const *const envp)
{
	register int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (g_status.exit = OK);
}

int
	builtin_env(const t_command *const cmd)
{
	(void)cmd;
	return (print_env((const char **)g_status.env.envp));
}
