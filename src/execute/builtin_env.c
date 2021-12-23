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
	const t_declare		*node = g_status.env.head;
	char				**envp;
	register int		i;

	if (!g_status.env.edited)
		return ;
	envp = xcalloc(sizeof(char *) * g_status.env.envc + 1);
	i = -1;
	while (node && (++i < g_status.env.envc))
	{
		if (node->line && node->exported)
			envp[i] = node->line;
		node = node->next;
	}
	xfree(g_status.env.envp);
	g_status.env.envp = envp;
	g_status.env.edited = FALSE;
}

int
	builtin_env(const t_command *const cmd)
{
	const t_declare	*node = g_status.env.head;

	(void)cmd;
	while (node)
	{
		if (node->exported && node->line)
			printf("%s\n", node->line);
		node = node->next;
	}
	return (g_status.exit = OK);
}
