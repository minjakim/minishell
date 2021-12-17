/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 18:45:18 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	mini_null(const t_command *const command)
{
	(void)command;
	return (SUCCESS);
}

int
	mini_execve(const t_command *const command)
{
	g_status.haschild = 0;
	if (!(command->flags & CMD_NO_FORK))
		g_status.haschild = fork();
	if (g_status.haschild == 0)
	{
		if (execve(command->path, command->argv, g_status.env.envp) == ERROR)
		{
			if (exception_error(command->argv[0], NULL, errno) == ENOENT)
				exit(EX_NOTFOUND);
			exit(EX_NOEXEC);
		}
		exit(OK);
	}
	else if (g_status.haschild > 0)
		if (waitpid(g_status.haschild, &g_status.exit, 0) != ERROR)
			return (g_status.exit);
	return (exception_error(NULL, NULL, errno));
}
