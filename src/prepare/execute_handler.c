/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 19:28:49 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	execute_handler(t_command *cmd)
{
	while (cmd)
	{
		if ((cmd->flags & CMD_PIPE) && xfork() == 0)
			cmd->flags |= CMD_NO_FORK;
		if (g_status.haschild == 0)
		{
			expand_command(cmd);
			if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				redirect_io(cmd);
			set_io(&cmd->io);
			g_status.execute[find_command(cmd)]((const t_command*)cmd);
		}
		if (g_status.haschild && !(cmd->flags & CMD_IGNORE_RETURN))
		{
			if (waitpid(g_status.haschild, &g_status.exit, 0) == ERROR)
				report_error(NULL, NULL, errno);
			if (g_status.exit && g_status.exit <= SIGUSR2)
				signal_report(g_status.exit);
			while (wait(NULL) != ERROR)
				;
		}
		close_io(&cmd->io);
		cmd = cmd->next;
	}
	g_status.haschild = FALSE;
	return (SUCCESS);
}
