/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:40:38 by snpark            #+#    #+#             */
/*   Updated: 2021/10/04 11:04:25 by snpark           ###   ########.fr       */
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
		if (cmd.stream_in != 0)
			dup2(cmd.stream_in, 0);
		if(*command == '.' || *command == '~' || *command == '/')
			execve(command, cmd.argv, env);
		else
			ft_execve(cmd.argv, env);
	}
	else if (fd > 0)
	{
		if (cmd.stream_in != 0)
			close(cmd.stream_in);
		if (cmd.stream_out != 0)
			close(cmd.stream_out);
		wait(NULL);
		printf("done");
	}
	return (0);
}
