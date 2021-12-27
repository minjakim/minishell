/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/27 13:48:10 by minjakim         ###   ########.fr       */
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
		if (node->next)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		else
			g_status.env.tail = node->prev;
	}
	node->prev = NULL;
	node->next = NULL;
	if (node->type != K_ONLY)
	{
		--g_status.env.envc;
		g_status.env.edited = TRUE;
	}
	g_status.env.tail->next = NULL;
	disposer(node->key.str, node->value.str, node->line, node);
}

int
	builtin_unset(const t_command *const cmd)
{
	t_declare	*node;
	char		**argv;
	int			exception;
	t_dc		dc;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (g_status.exit = OK);
	while (*++argv)
	{
		dc = declare_legal_check(*argv);
		if (dc.type != K_ONLY && ++exception)
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
