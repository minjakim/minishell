/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 13:12:37 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	mini_null(t_shell *mini)
{
	(void)mini;
	return (0);
}

int
	mini_execve(t_shell *mini)
{
	const t_command	*const command = mini->command;
	pid_t			pid;

	if (command->flags & CMD_NOFUNCTION)
		return (0);
	pid = 0;
	if (!(command->flags & CMD_NO_FORK))
		pid = fork();
	if (pid == 0)
	{
		if (execve(command->path, command->argv, mini->env.envp) == ERROR)
			exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &mini->status->exit, 0);
		return (mini->status->exit);
	}
	else if (pid < 0)
		return (1);
	return (0);
}
