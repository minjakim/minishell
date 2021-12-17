/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 14:16:40 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/17 21:56:49 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	command_io_close(t_io io)
{
	if (io.in != STDIN_FILENO)
		close(io.in);
	if (io.out != STDOUT_FILENO)
		close(io.out);
}

int
	command_io_set(t_io io)
{
	if (dup2(io.in, STDIN_FILENO) == ERROR)
		return (FAILURE);
	if (dup2(io.out, STDOUT_FILENO) == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

int
	command_pipe_set(t_command *command)
{
	pid_t		pid;

	command_io_set(command->io);
	pid = fork();
	if (pid == 0)
		g_status.interactive = FALSE;
	if (pid > 0 && !(command->flags & CMD_IGNORE_RETURN))
	{
		waitpid(pid, &g_status.exit, 0);
		while (wait(NULL) != -1)
			;
	}
	return (pid);
}
