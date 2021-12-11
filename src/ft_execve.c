/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 16:18:03 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	ft_execve(t_shell *mini)
{
	pid_t	pid;

	if (mini->command->flags & CMD_NOFUNCTION)
		return (0);
	pid = 0;
	if (!(mini->command->flags & CMD_NO_FORK))
		pid = fork();
	if (pid == 0)
	{
		if (execve(mini->command->value.simple.path, mini->command->value.simple.argv, mini->env.envp) == ERROR)
			exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &mini->status.exit, 0);
		return (mini->status.exit);
	}
	else if (pid < 0)
		return (1);
	return (0);
}
