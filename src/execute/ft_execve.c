/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:29:14 by snpark            #+#    #+#             */
/*   Updated: 2021/12/09 15:14:01 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	ft_execve(t_shell *mini)
{
	pid_t	pid;

	if (mini->cmd->flags & CMD_NOFUNCTION)
		return (0);
	pid = 0;
	if (!(mini->cmd->flags & CMD_NO_FORK))
		pid = fork();
	if (pid == 0)
	{
		if (execve(mini->cmd->value.simple.path, mini->cmd->value.simple.argv, mini->env.envp) == -1)
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
