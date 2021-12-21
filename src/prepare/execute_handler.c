/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/21 10:18:40 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_proceed(t_command *cmd)
{
	if (cmd->connector & W_PIPE)
		return (TRUE);
	if (cmd->connector & W_AND_AND && g_status.exit == OK)
		return (TRUE);
	if (cmd->connector & W_OR_OR && g_status.exit != OK)
		return (TRUE);
	return (FALSE);
}

int
	execute_handler(t_command *cmd)
{
	while (cmd)
	{
		if ((cmd->flags & CMD_PIPE) && xfork() == 0)
		{
			cmd->flags |= CMD_NO_FORK;
			set_io(&cmd->io);
		}
		if (g_status.state.haschild == 0)
		{
			if (!expand_command(cmd))
				return (FAILURE);
			if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				redirect_io(cmd);
			g_status.execute[find_command(cmd)]((const t_command*)cmd);
			if (cmd->flags & CMD_PIPE)
				exit(g_status.exit);
		}
		if (g_status.state.haschild && !(cmd->flags & CMD_IGNORE_RETURN))
		{
			if (waitpid(g_status.state.haschild, &g_status.exit, 0) == ERROR)
				report_error(NULL, NULL, errno);
			if (g_status.exit && g_status.exit <= SIGUSR2)
				signal_report(g_status.exit);
			while (wait(NULL) != ERROR)
				;
		}
		reset_io(&cmd->io);
		if (is_proceed(cmd))
			cmd = cmd->next;
	}
	g_status.state.haschild = FALSE;
	return (SUCCESS);
}
