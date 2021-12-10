/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/10 14:14:00 by snpark           ###   ########.fr       */
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

static void 
	close_io(t_io io)
{
	if (io.in != STDIN_FILENO)
		close(io.in);
	if (io.out != STDOUT_FILENO)
		close(io.out);
}

static int
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
		mini->status.interactive = 0;
	if (pid > 0 && cmd->type == cm_simple)
	{
		waitpid(pid, &mini->status.exit, 0); 
		while (wait(NULL) != -1)
			;
	}
	return (pid);
}

static int
	next_cmd(t_command *cmd)
{
	return (cmd->type == cm_connection);// && \
//			(cmd->value.connection.connector == "&&" && exit_status == 0 || \
//			 cmd->value.connection.connector == "||" && exit_status != 0 || \
//			 cmd->value.connection.connector == "|"));
}

int
	execute_cmd(t_shell *mini)
{
	t_command	*cmd;
	pid_t		pid;
	t_io		pipe_fd;

	cmd = mini->cmd;
	while (cmd)
	{
		pid = 0;
		if (cmd->flags & CMD_PIPE)
			pid = set_pipe(mini);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			expand_cmd(mini);
			if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				redirect(mini);
			find_cmd(mini);
			mini->execute[is_builtin(mini->cmd->value.simple.argv[0])](mini);
			//if (expand_cmd() != 0)
			//	return (1);
			//if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			//	if (redirect() != 0)
			//		return (1);
			//if (find_cmd() != 0)
			//	return (127);
			//mini->err.exit_status = shell_execve[is_builtin()](mini);
			if (mini->status.interactive == 0)
				exit(mini->status.exit);
		}
		//close_io(cmd->value.simple.io);
		//redirect_stdio(mini->backup.io);
		if (next_cmd(cmd))
			cmd = cmd->value.connection.next;
		else
			return (0);
	}
	return (0);
}
