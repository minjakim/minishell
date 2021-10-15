/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:27:17 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	is_builtin(const char *command, t_command cmd, char **envp)
{
	int	stream_out;
	int	stream_in;

	if (cmd.stream_out == 1 && cmd.out_pipe != 0)
		stream_out = cmd.out_pipe;
	else
		stream_out = cmd.stream_out;
	if (cmd.stream_in == 0 && cmd.in_pipe != 0)
		stream_in = cmd.in_pipe;
	else
		stream_in = cmd.stream_in;
	if (!strcmp(command, "echo"))
		return (echo(cmd.argv, envp, stream_in, stream_out));
	if (!strcmp(command, "cd"))
		return (cd(cmd.argv, envp));
	if (!strcmp(command, "pwd"))
		return (pwd(cmd.argv, envp, stream_out));
	if (!strcmp(command, "export"))
		return (ms_export(cmd.argv, envp, stream_in, stream_out));
	if (!strcmp(command, "unset"))
		return (ms_unset(cmd.argv, envp));
	if (!strcmp(command, "env"))
		return (ms_env(cmd.argv, envp, stream_out));
	if (!strcmp(command, "exit"))
		return (ms_exit(1));//ms_exit(exit_status)
	return (0);
}

int
	shell_execve(t_command cmd, char **env)
{
	pid_t	fd;
	int		built_in;
	const char	*command = cmd.argv[0];
	int		exit_status;

	fd = 1;
	built_in = 0;
	if (is_builtin(command, cmd, env))
		built_in = 1;
	else
		fd = fork();
	if (fd == 0)
	{
		if (cmd.stream_out != 1)
			dup2(cmd.stream_out, 1);
		else if (cmd.out_pipe)
			dup2(cmd.out_pipe, 1);
		if (cmd.stream_in != 0)
			dup2(cmd.stream_in, 0);
		else if (cmd.in_pipe)
			dup2(cmd.in_pipe, 0);
		if(*command == '.' || *command == '~' || *command == '/')
			execve(command, cmd.argv, env);
		else
			ft_execve(cmd.argv, env);
	}
	else if (fd > 0 || built_in)
	{
		if (cmd.stream_in != 0)
			close(cmd.stream_in);
		if (cmd.stream_out != 1)
			close(cmd.stream_out);
		if (cmd.out_pipe)
			close(cmd.out_pipe);
		if (cmd.in_pipe)
			close(cmd.in_pipe);
		if (fd > 0)
			waitpid(fd, &exit_status, 0);
	}
	return (0);
}
