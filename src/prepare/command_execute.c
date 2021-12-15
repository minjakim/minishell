/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 10:03:00 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	command_execute(t_shell *mini)
{
	const t_command	*command = mini->command;
	pid_t			pid;
	t_io			pipe_fd;

	while (command)
	{
		pid = 0;
		if (command->flags & CMD_PIPE)
			pid = command_pipe_set(mini);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			expand_command(mini);
			if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				command_redirect(mini);
			//mini->execute[is_builtin(command->value.simple.argv[0])](mini);
			//if (expand_command() != 0)
			//	return (1);
			//if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			//	if (redirect() != 0)
			//		return (1);
			//if (find_command() != 0)
			//	return (127);
			//mini->err.exit_status = shell_execve[is_builtin()](mini);
			if (g_status.interactive == 0)
				exit(g_status.exit);
		}
		//close_io(command->value.simple.io);
		//redirect_stdio(mini->backup.io);
		if (command->next)
			command = command->next;
		else
			return (0);
	}
	return (0);
}
