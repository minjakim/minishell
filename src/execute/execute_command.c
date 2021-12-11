/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 10:03:00 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	redirect_stdio(t_io *io)
{
	if (dup2(io->in, STDIN_FILENO) == ERROR)
		return (1);
	if (dup2(io->out, STDOUT_FILENO) == ERROR)
		return (1);
	return (0);
}

static void
	close_io(t_io *io)
{
	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
}

static int
	set_pipe(t_shell *mini)
{
	t_command	*command;
	pid_t		pid;
	t_io		pipe_fd;

	command = mini->command;
	if (command->type == cm_connection && \
			command->value.connection.connector == '|')
	{
		pipe(pipe_fd.fd);
		command->value.connection.io.out = pipe_fd.in;
		command->value.connection.next->value.simple.io.in = pipe_fd.out;
	}
	redirect_stdio(&command->value.connection.io);
	pid = fork();
	if (pid == 0)
		mini->status.interactive = 0;
	if (pid > 0 && command->type == cm_simple)
	{
		waitpid(pid, &mini->status.exit, 0);
		while (wait(NULL) != -1)
			;
	}
	return (pid);
}

static int
	next_command(t_command *command)
{
	return (command->type == cm_connection);// && \
//			(command->value.connection.connector == "&&" && exit_status == 0 || \
//			 command->value.connection.connector == "||" && exit_status != 0 || \
//			 command->value.connection.connector == "|"));
}

int
	execute_command(t_shell *mini)
{
	t_command	*command;
	pid_t		pid;
	t_io		pipe_fd;

	command = mini->command;
	while (command)
	{
		pid = 0;
		if (command->flags & CMD_PIPE)
			pid = set_pipe(mini);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			expand_command(mini);
			if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				redirect(mini);
			//mini->execute[is_builtin(command->value.simple.argv[0])](mini);
			//if (expand_command() != 0)
			//	return (1);
			//if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			//	if (redirect() != 0)
			//		return (1);
			//if (find_command() != 0)
			//	return (127);
			//mini->err.exit_status = shell_execve[is_builtin()](mini);
			if (mini->status.interactive == 0)
				exit(mini->status.exit);
		}
		//close_io(command->value.simple.io);
		//redirect_stdio(mini->backup.io);
		if (next_command(command))
			command = command->value.connection.next;
		else
			return (0);
	}
	return (0);
}
