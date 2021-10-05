/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/10/05 18:23:28 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/10/05 18:23:10 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	shell_execve(t_command cmd, char **env)
{
	pid_t	fd;
	const char	*command = cmd.argv[0];

	//if (command == built_in function)	
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
	else if (fd > 0)
	{
		if (cmd.stream_in != 0)
			close(cmd.stream_in);
		if (cmd.stream_out != 1)
			close(cmd.stream_out);
		if (cmd.out_pipe)
			close(cmd.out_pipe);
		if (cmd.in_pipe)
			close(cmd.in_pipe);
		wait(NULL);
	}
	return (0);
}
