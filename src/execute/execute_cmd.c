/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/11/11 15:11:13 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_builtin(const char *command, t_command cmd, char **envp, t_hash **ex_list)
{
	t_io	stream;

	if (cmd.stream.out == 1 && cmd.pipe.out != 0)
		stream.out = cmd.pipe.out;
	else
		stream.out = cmd.stream.out;
	if (cmd.stream.in == 0 && cmd.pipe.in != 0)
		stream.in = cmd.pipe.in;
	else
		stream.in = cmd.stream.in;
	if (!strcmp(command, "echo"))
		return (builtin_echo(cmd.argv, envp, stream));
	if (!strcmp(command, "cd"))
		return (cd(cmd.argv, envp));
	if (!strcmp(command, "pwd"))
		return (pwd(cmd.argv, envp, stream.out));
	if (!strcmp(command, "export"))
		return (ms_export(cmd.argv, envp, stream, ex_list));
	if (!strcmp(command, "unset"))
		return (ms_unset(cmd.argv, envp, ex_list));
	if (!strcmp(command, "env"))
		return (ms_env(cmd.argv, envp, stream.out));
	if (!strcmp(command, "exit"))
		return (ms_exit(1));//ms_exit(exit_status)
	if (command == NULL || !strcmp(command, ":"))
		return (1);
	return (0);
}

int
	shell_execve(t_command cmd, char **env, t_hash **export_list)
{
	const char	*command = cmd.argv[0];
	const int	built_in = is_builtin(command, cmd, env, export_list);
	pid_t		fd;
	int			exit_status;

	fd = 1;
	if (!built_in)
		fd = fork();
	if (fd == 0)
	{
		if (cmd.stream.out != 1)
		{
			close(1);
			dup2(cmd.stream.out, 1);
		}
		if (cmd.stream.in != 0)
		{
			close(0);
			dup2(cmd.stream.in, 0);
		}
		if (*command == '.' || *command == '~' || *command == '/')
			//stat()으로 파일인지 체크하는 방법도 있을듯
			execve(command, cmd.argv, env);
		else
			ft_execve(cmd.argv, env);
	}
	else if (fd > 0 && (cmd.pipe.out != -1 || cmd.pipe.in != -1))
	{
		//sub shell이 자식프로세스를 기다리는 것
		if (!built_in)
			waitpid(fd, &exit_status, 0);
		exit(exit_status);
	}
	else if (fd > 0)
	{
		if (cmd.stream.in != 0)
			close(cmd.stream.in);
		if (cmd.stream.out != 1)
			close(cmd.stream.out);
		if (!built_in)
			waitpid(fd, &exit_status, 0);
	}
	return (0);
}
