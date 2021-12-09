/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/09 12:17:47 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	init_builtins(t_shell *mini)
{
	mini->execute[FT_EXECVE] = ft_execve;
	mini->execute[MINI_CD] = mini_cd;
	mini->execute[MINI_ECHO] = mini_echo;
	mini->execute[MINI_ENV] = mini_env;
	mini->execute[MINI_EXIT] = mini_exit;
	mini->execute[MINI_EXPORT] = mini_export;
	mini->execute[MINI_PWD] = mini_pwd;
	mini->execute[MINI_UNSET] = mini_unset;
	mini->execute[MINI_NULL] = mini_null;
}

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
	init_builtins(mini);
	return (0);
}
