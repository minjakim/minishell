/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 17:18:04 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	init_execute(void)
{
	g_status.execute[MINI_EXECVE] = mini_execve;
	g_status.execute[FT_CD] = builtin_cd;
	g_status.execute[FT_ECHO] = builtin_echo;
	g_status.execute[FT_ENV] = builtin_env;
	g_status.execute[FT_EXIT] = builtin_exit;
	g_status.execute[FT_EXPORT] = builtin_export;
	g_status.execute[FT_PWD] = builtin_pwd;
	g_status.execute[FT_UNSET] = builtin_unset;
	g_status.execute[FT_NULL] = mini_null;
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

static int
	init_status(void)
{
	g_status.exit = 0;
	g_status.interactive = TRUE;
	g_status.heredoc.value = 0;
	tgetent(NULL, "xterm");
	if (!init_env(&g_status.env))
		return (FAILURE);
	if (!init_io(&g_status.backup.stdio))
		return (FAILURE);
	if (tcgetattr(STDIN_FILENO, &g_status.backup.attr) == ERROR)
	{
		g_status.exit = GENERAL_ERROR;
		return (FAILURE);
	}
	return (SUCCESS);
}

int
	initialize()
{
	init_status();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	rl_catch_signals = FALSE;
	init_execute();
	return (SUCCESS);
}
