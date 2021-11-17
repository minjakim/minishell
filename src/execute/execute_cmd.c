/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:24:06 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_builtin(t_command cmd, char **envp, t_hash **ex_list, int *exit_status)
{
	const char	*command = cmd.argv[0];
	t_io	stream;

	if (cmd.stream.out == 1 && cmd.pipe.out != -1)
		stream.out = cmd.pipe.out;
	else
		stream.out = cmd.stream.out;
	if (cmd.stream.in == 0 && cmd.pipe.in != -1)
		stream.in = cmd.pipe.in;
	else
		stream.in = cmd.stream.in;
	if (!strcmp(command, "echo"))
		return (builtin_echo(cmd.argv, stream, exit_status));
	if (!strcmp(command, "cd"))
		return (cd(cmd.argv, envp, exit_status));
	if (!strcmp(command, "pwd"))
		return (pwd(stream.out, exit_status));
	if (!strcmp(command, "export"))
		return (ms_export(cmd, envp, ex_list, exit_status));
	if (!strcmp(command, "unset"))
		return (ms_unset(cmd.argv, envp, ex_list, exit_status));
	if (!strcmp(command, "env"))
		return (ms_env(cmd.argv, envp, stream.out, exit_status));
	if (!strcmp(command, "exit"))
		return (ms_exit(cmd.argv, cmd.pipe, exit_status));//ms_exit(exit_status)
	if (command == NULL || !strcmp(command, ":") || *command == '\0')
	{
		*exit_status = 0;
		return (1);
	}
	return (0);
}

void bash_arg_err(const char *arg)
{
	write(2, "bash: ", 6);
	write(2, arg, strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

void
	bash_cmd_arg_err(const char *cmd, const char *arg)
{
	write(2, "bash: ", 6);
	write(2, cmd, strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

void cmd_arg_err(const char *cmd, const char *arg)
{
	write(2, cmd, strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

int
	shell_execve(t_command cmd, char **env, t_hash **export_list, int *exit_status)
{
	const char	*command = cmd.argv[0];
	const int	built_in = is_builtin(cmd, env, export_list, exit_status);
	pid_t		fd;

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
		{
			//stat()으로 파일인지 체크하는 방법도 있을듯
			if (execve(command, cmd.argv, env) == -1)
			{
				if (errno == EACCES)
					*exit_status = 126;/*파일은 있는데 실행을 못함*/
				else
					*exit_status = 127;/*실행할 파일이 없음*/	
				bash_arg_err(command);
			}
		}
		else
			ft_execve(cmd.argv, env, exit_status);
	}
	else if (fd > 0 && (cmd.pipe.out != -1 || cmd.pipe.in != -1))
	{
		//sub shell이 자식프로세스를 기다리는 것
		if (!built_in)
			waitpid(fd, exit_status, 0);
		exit(*exit_status);
	}
	else if (fd > 0)
	{
		if (cmd.stream.in != 0)
			close(cmd.stream.in);
		if (cmd.stream.out != 1)
			close(cmd.stream.out);
		if (!built_in)
			waitpid(fd, exit_status, 0);
	}
	return (0);
}
