/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 12:09:47 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	init_builtins(t_shell *mini)
{
	mini->execute[FT_EXECVE] = ft_execve;
	mini->execute[MINI_CD] = builtin_cd;
	mini->execute[MINI_ECHO] = builtin_echo;
	mini->execute[MINI_ENV] = builtin_env;
	mini->execute[MINI_EXIT] = builtin_exit;
	mini->execute[MINI_EXPORT] = builtin_export;
	mini->execute[MINI_PWD] = builtin_pwd;
	mini->execute[MINI_UNSET] = builtin_unset;
	mini->execute[MINI_NULL] = builtin_null;
}

static int
	backup_stdio(t_ios *mini)
{
	mini->backup.in= dup(STDIN_FILENO);
	if (mini->backup.in == ERROR)
		return (FAIL);
	mini->backup.out = dup(STDOUT_FILENO);
	if (mini->backup.out == ERROR)
		return (FAIL);
	return (SUCCESS);
}

int
	initialize(t_shell *mini)
{
	if (!backup_stdio(&mini->ios))
		return (FAIL);
	if (!parse_envp(&mini->env))
		return (FAIL);
	init_builtins(mini);
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, &mini->config.current);
	mini->config.backup = mini->config.current;
	mini->config.current.c_cc[VQUIT] = FALSE;
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
	signal(SIGINT, handler_signal);
	rl_catch_signals = FALSE;
	mini->command = NULL;
	mini->status.exit = 0;
	mini->status.interactive = TRUE;
	mini->status.error = 0;
	return (SUCCESS);
}
