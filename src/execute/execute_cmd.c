/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/05 12:55:39 by snpark           ###   ########.fr       */
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

	if (cmd->type == cm_connection && \
			cmd->value.connection.connector == '|')
	{
		pipe(pipe_fd.fd);
		cmd->value.connection.stream.out = pipe_fd.in;
		cmd->value.connection.next->value.simple.stream.in = pipe_fd.out;
	}	
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
			set_pipe();
		if (cmd->type == cm_connection && \
				cmd->value.connection.connector == '|')
		{
			pipe(pipe_fd.fd);
			cmd->value.connection.stream.out = pipe_fd.in;
			cmd->value.connection.next->value.simple.stream.in = pipe_fd.out;
			pid = fork();
			if (pid == 0)
				mini->internal = 0;
			else if (pid < 0)
				return (1);//error
		}
		if (!pid)
		{
		//expand_cmd();
		//find_cmd();
		//redirect();
		//exit_status = ft_execve();
		}
		if (cmd->type == cm_connection)
			cmd = cmd->value.connection.next;
		else if (cmd->type == cm_simple)
			return (0);
	}
	return (0);
}
