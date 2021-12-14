/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 13:06:59 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	init_execute(t_shell *mini)
{
	mini->execute[FT_EXECVE] = mini_execve;
	mini->execute[MINI_CD] = builtin_cd;
	mini->execute[MINI_ECHO] = builtin_echo;
	mini->execute[MINI_ENV] = builtin_env;
	mini->execute[MINI_EXIT] = builtin_exit;
	mini->execute[MINI_EXPORT] = builtin_export;
	mini->execute[MINI_PWD] = builtin_pwd;
	mini->execute[MINI_UNSET] = builtin_unset;
	mini->execute[MINI_NULL] = mini_null;
}

static int
	init_io(t_io *io)
{
	io->in = dup(STDIN_FILENO);
	if (io->in == ERROR)
		return (FAILURE);
	io->out = dup(STDOUT_FILENO);
	if (io->out == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

static int
	init_env(t_env *env)
{
	return (SUCCESS);
}

int
	initialize(t_shell *mini)
{
	if (!init_env(&mini->env))
		return (FAILURE);
	if (!init_io(&mini->backup.stdio))
		return (FAILURE);
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, &mini->backup.attr);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	rl_catch_signals = FALSE;
	mini->status->haschild = FALSE;
	mini->command = NULL;
	init_execute(mini);
	return (SUCCESS);
}
