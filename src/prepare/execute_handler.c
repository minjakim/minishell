/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 21:28:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	pre_excute(t_command *cmd)
{
	expand_command(cmd);
	if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
		redirect_io(cmd);
	set_io(&cmd->io);
	return (find_command(cmd));
}

int
	execute_handler(t_command *cmd)
{
	while (cmd)
	{
		if ((cmd->flags & CMD_PIPE) && xfork() == 0)
			cmd->flags |= CMD_NO_FORK;
		if (g_status.state.haschild == 0)
		{
			g_status.execute[pre_excute(cmd)]((const t_command*)cmd);
			if (cmd->flags & CMD_PIPE)
				exit(g_status.exit);
		}
		if (g_status.state.haschild && !(cmd->flags & CMD_IGNORE_RETURN))
			xwait(g_status.state.haschild);
		reset_io(&cmd->io);
		cmd = cmd->next;
	}
	g_status.state.haschild = FALSE;
	return (SUCCESS);
}
