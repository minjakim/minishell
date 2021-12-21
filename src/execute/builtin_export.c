/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 20:56:00 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_declare(t_declare *node)
{
	while (node)
	{
		if (node->exported)
		{
			printf("declare -x %s", node->key);
			if (node->value)
				printf("=\"%s\"\n", node->value);
			node = node->next;
		}
	}
	return (SUCCESS);
}

int
	builtin_export(const t_command *const cmd)
{
	char	**argv;

	argv = cmd->argv;
	if (argv[0] != NULL && argv[1] == NULL)
		return (print_declare(g_status.env.head));
	while (*++argv)
	{
		if (declare_check(*argv) == ERROR)
			return (GENERAL_ERROR);
		declare_add(*argv)->exported = TRUE;
	}
	declare_update_envp();
	return (g_status.exit = OK);
}
