/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 17:23:20 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	mini_null(const t_command *const cmd)
{
	(void)cmd;
	return (SUCCESS);
}

int
	mini_execve(const t_command *const cmd)
{
	g_status.haschild = 0;
	if (!(cmd->flags & CMD_NO_FORK))
		g_status.haschild = fork();
	if (g_status.haschild == 0)
	{
		if (execve(cmd->path, cmd->argv, g_status.env.envp) == ERROR)
		{
			if (report_error(cmd->argv[0], NULL, errno) == ENOENT)
				exit(ES_NOTFOUND);
			exit(ES_NOEXEC);
		}
		exit(OK);
	}
	else if (g_status.haschild > 0)
		if (waitpid(g_status.haschild, &g_status.exit, 0) != ERROR)
			return (g_status.exit);
	return (report_error(NULL, NULL, errno));
}
