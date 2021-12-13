/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 11:17:09 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	mini->execute[MINI_NULL] = builtin_null;
}

static int
	init_io(t_io *io)
{
	io->in = dup(STDIN_FILENO);
	if (io->in == ERROR)
		return (FAIL);
	io->out = dup(STDOUT_FILENO);
	if (io->out == ERROR)
		return (FAIL);
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
	t_termios	attr;

	if (!init_io(&mini->backup.stdio))
		return (FAIL);
	if (!init_env(&mini->env))
		return (FAIL);
	init_execute(mini);
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, &attr);
	mini->backup.attr = attr;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	signal(SIGINT, handler_signal);
	rl_catch_signals = FALSE;
	mini->command = NULL;
	mini->status.interactive = TRUE;
	mini->status.exit = 0;
	mini->status.error = 0;
	return (SUCCESS);
}
