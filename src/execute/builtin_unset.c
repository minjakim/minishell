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

static int
	declare_unset(const char *str, t_declare *node)
{
	t_declare	*temp;

	if (node && !ft_strcmp(str, node->key.str))
	{
		temp = g_status.env.head;
		g_status.env.head = g_status.env.head->next;
	}
	else
	{
		while (node && node->next && ft_strcmp(str, node->next->key.str))
			node = node->next;
		temp = node->next;
		node->next = temp->next;
	}
	disposer(temp->key.str, temp->value.str, temp, NULL);
	if (node && node->next == NULL)
		g_status.env.tail = node;
	--g_status.env.envc;
	return (g_status.env.edited = TRUE);
}

int
	builtin_unset(const t_command *const cmd)
{
	char	**argv;
	int		exception;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (g_status.exit = OK);
	printf("%d	%d\n", g_status.env.envc, declare_search(cmd->argv[1]) != NULL);
	while (*++argv)
	{
		if (!declare_legal_check(*argv) && ++exception)
			report_exception(cmd->argv[0], *argv, EX_DECLARE, GENERAL_ERROR);
		else
		{
			if (declare_search(*argv))
				declare_unset(*argv, g_status.env.head);
		}
	}
	declare_update_envp();
	printf("%d	%d\n", g_status.env.envc, declare_search(cmd->argv[1]) != NULL);
	if (exception)
		return (g_status.exit = GENERAL_ERROR);
	return (g_status.exit = OK);
}
