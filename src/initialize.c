/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 14:54:21 by minjakim         ###   ########.fr       */
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

static void
	init_term(t_termios *attr)
{
	attr->c_iflag = 27394;
	attr->c_oflag = 3;
	attr->c_cflag = 19200;
	attr->c_lflag = 536872395;
	attr->c_cc[0] = 4;
	attr->c_cc[1] = 255;
	attr->c_cc[2] = 255;
	attr->c_cc[3] = 127;
	attr->c_cc[4] = 23;
	attr->c_cc[5] = 21;
	attr->c_cc[6] = 18;
	attr->c_cc[7] = 255;
	attr->c_cc[8] = 3;
	attr->c_cc[9] = 28;
	attr->c_cc[10] = 26;
	attr->c_cc[11] = 25;
	attr->c_cc[12] = 17;
	attr->c_cc[13] = 19;
	attr->c_cc[14] = 22;
	attr->c_cc[15] = 15;
	attr->c_cc[16] = 1;
	attr->c_cc[17] = 0;
	attr->c_cc[18] = 20;
	attr->c_cc[19] = 255;
}

static int
	init_status(void)
{
	t_termios	attr;

	g_status.exit = 0;
	g_status.interactive = TRUE;
	g_status.heredoc.value = 0;
	g_status.need_heredoc = 0;
	if (!init_env(&g_status.env))
		return (FAILURE);
	if (!init_io(&g_status.backup.stdio))
		return (FAILURE);
	if (tcgetattr(STDIN_FILENO, &g_status.backup.attr) == ERROR)
	{
		g_status.exit = GENERAL_ERROR;
		return (FAILURE);
	}
	init_term(&attr);
	attr.c_ispeed = 9600;
	attr.c_ospeed = 9600;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == ERROR)
	{
		g_status.exit = GENERAL_ERROR;
		return (FAILURE);
	}
	return (SUCCESS);
}

int
	initialize(void)
{
	init_status();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	rl_catch_signals = FALSE;
	init_execute();
	return (SUCCESS);
}
