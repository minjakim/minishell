/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/06 10:43:21 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	redirect_stdio(t_io io)
{
	if (dup2(io.in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(io.out, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int
	set_pipe(t_shell *mini)
{
	t_command	*cmd;
	pid_t		pid;
	t_io		pipe_fd;

	cmd = mini->cmd;
	if (cmd->type == cm_connection && \
			cmd->value.connection.connector == '|')
	{
		pipe(pipe_fd.fd);
		cmd->value.connection.io.out = pipe_fd.in;
		cmd->value.connection.next->value.simple.io.in = pipe_fd.out;
	}
	redirect_stdio(cmd->value.connection.io);
	pid = fork();
	if (pid == 0)
		mini->interactive = 0;
	return (pid);
}

int
	execute_cmd(t_shell *mini)
{
	t_command	*cmd;
	pid_t		pid;
	t_io		pipe_fd;

	cmd = mini->cmd;
	pid = 0;
	while (cmd)
	{
		if (cmd->flags & CMD_PIPE)
			pid = set_pipe(mini);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			//expand_cmd();
			//if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			//	redirect();
			//find_cmd();
			//mini->err.exit_status = shell_execve[is_builtin()](mini);
			if (mini->interactive == 0)
				exit(mini->err.exit_status);
		}
		if (pid > 0 && cmd->type == cm_simple)
		{
			waitpid(pid, &mini->err.exit_status, 0); 
			while (wait(NULL) != -1)
				;
		}
		//redirect_stdio(mini->backup.io);
		if (cmd->type == cm_connection)
			cmd = cmd->value.connection.next;
		else if (cmd->type == cm_simple)
			return (0);
	}
	return (0);
}
