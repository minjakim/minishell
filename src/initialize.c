/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 20:55:48 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	init_execute(void)
{
	g_status.execute[NOTFOUND] = mini_null;
	g_status.execute[MINI_NULL] = mini_null;
	g_status.execute[FT_CD] = builtin_cd;
	g_status.execute[FT_ECHO] = builtin_echo;
	g_status.execute[FT_ENV] = builtin_env;
	g_status.execute[FT_EXIT] = builtin_exit;
	g_status.execute[FT_EXPORT] = builtin_export;
	g_status.execute[FT_PWD] = builtin_pwd;
	g_status.execute[FT_UNSET] = builtin_unset;
	g_status.execute[MINI_EXECVE] = mini_execve;
}

static int
	init_io(t_io *io)
{
	io->in = dup(STDIN_FILENO);
	if (io->in == ERROR)
		return (report_error_fatal(errno));
	io->out = dup(STDOUT_FILENO);
	if (io->out == ERROR)
		return (report_error_fatal(errno));
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

	g_status.state.prompt = sizeof(PROMPT);
	g_status.interactive = TRUE;
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
	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	rl_catch_signals = FALSE;
	rl_event_hook = event_hook;
	return (SUCCESS);
}

int
	init_declare(void)
{
	extern char	**environ;
	char		**envp;

	envp = environ;
	g_status.env.envc = -1;
	if (envp[++g_status.env.envc])
	{
		g_status.env.head = declare_new(envp[g_status.env.envc]);
		g_status.env.head->exported = TRUE;
		g_status.env.tail = g_status.env.head;
		while (envp[++g_status.env.envc])
			(declare_add(envp[g_status.env.envc]))->exported = TRUE;
		if (!declare_search(OLDPWD))
			declare_add(OLDPWD)->exported = TRUE;
	}
	g_status.env.envp = NULL;
	g_status.env.edited = TRUE;
	declare_update_envp();
	return (SUCCESS);
}

int
	initialize(void)
{
	init_status();
	init_signal();
	init_execute();
	init_declare();
	return (SUCCESS);
}
