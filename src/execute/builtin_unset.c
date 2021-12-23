/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void
	declare_unset(t_declare *node)
{
	if (node->prev == NULL)
	{
		g_status.env.head = g_status.env.head->next;
		g_status.env.head->prev = NULL;
	}
	else
	{
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		else
			g_status.env.tail = node->prev;
	}
	--g_status.env.envc;
	g_status.env.edited = TRUE;
	disposer(node->key.str, node->value.str, node, NULL);
}

int
	builtin_unset(const t_command *const cmd)
{
	t_declare	*node;
	char		**argv;
	int			exception;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (g_status.exit = OK);
	while (*++argv)
	{
		if (!declare_legal_check(*argv) && ++exception)
			report_exception(cmd->argv[0], *argv, EX_DECLARE, GENERAL_ERROR);
		else
		{
			node = declare_search(*argv);
			if (node)
				declare_unset(node);
		}
	}
	declare_update_envp();
	if (exception)
		return (g_status.exit = GENERAL_ERROR);
	return (g_status.exit = OK);
}
