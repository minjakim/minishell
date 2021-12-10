/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/09 13:09:31 by snpark           ###   ########.fr       */
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
	mini->backup.in= dup(0);
	if (mini->backup.in == -1)
		return (1);
	mini->backup.out = dup(1);
	if (mini->backup.out == -1)
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
	init_builtins(mini);
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, &mini->config.current);
	mini->config.backup = mini->config.current;
	mini->config.current.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
	signal(SIGINT, signal_handler);
	rl_catch_signals = 0;
	mini->cmd = NULL;
	mini->status.exit = 0;
	mini->status.interactive = 1;
	mini->status.error = 0;
	return (0);
}
