/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/04 20:53:13 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int
	back_up_stdin_stdout(t_shell *mini)
{
	mini->stdin = dup(0);
	if (mini->stdin == -1)
		return (1);
	mini->stdout = dup(1);
	if (mini->stdout == -1)
		return (1);
	return (0);
}

int
	initialize(t_shell *mini)
{
	if (back_up_stdin_stdout(mini) != 0)
		return (1);
	if (parse_envp(&mini->env) != 0)
		return (1);
	mini->line = NULL;
	mini->list = NULL;
	mini->cmd = NULL;
	return (0);
}
