/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 12:15:18 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	mini_null(const t_command *const command)
{
	(void)command;
	return (OK);
}

int
	mini_execve(const t_command *const command)
{
	if ((command->flags & CMD_NO_FORK) || xfork() == 0)
	{
		if (execve(command->path, command->argv, g_status.env.envp) == ERROR)
		{
			if (report_error(command->argv[0], NULL, errno) == ENOENT)
				exit(ES_NOTFOUND);
			exit(ES_NOEXEC);
		}
	}
	return (g_status.exit = OK);
}
