/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:41:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/25 12:53:39 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	set_termios(t_termios *attr)
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

void
	init_status(void)
{
	g_status.state.prompt = sizeof(PROMPT);
	g_status.interactive = TRUE;
	g_status.backup.stdio.in = dup(STDIN_FILENO);
	if (g_status.backup.stdio.in == ERROR)
		report_error_fatal(errno);
	g_status.backup.stdio.out = dup(STDOUT_FILENO);
	if (g_status.backup.stdio.out == ERROR)
		report_error_fatal(errno);
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

void
	make_declare(void)
{
	char *const	path = getcwd(NULL, 0);

	if (path == NULL)
		report_error_fatal(errno);
	declare_update_node(PWD, path);
	declare_add(SHLVL_1);
	g_status.env.envc = 2;
	g_status.env.envp = NULL;
	g_status.env.edited = TRUE;
	xfree(path);
}

void
	init_declare(void)
{
	t_declare	*node;
	char		*shlvl;

	g_status.env.envc = -1;
	if (g_status.env.envp[++g_status.env.envc])
	{
		while (g_status.env.envp[++g_status.env.envc])
			declare_add(g_status.env.envp[g_status.env.envc]);
		node = declare_search(SHLVL);
		if (node == NULL && declare_add(SHLVL_1))
			++g_status.env.envc;
		else
		{
			shlvl = ft_itoshlvl(ft_shlvltoi(node->value.str));
			declare_export_update_value(node, shlvl, EXPORT);
			xfree(shlvl);
		}
	}
	g_status.env.envp = NULL;
	g_status.env.edited = TRUE;
}

void
	init_signal(void)
{
	t_termios	attr;

	set_termios(&attr);
	if (tcgetattr(STDIN_FILENO, &g_status.backup.attr) == ERROR)
		report_error_fatal(errno);
	attr.c_ispeed = 9600;
	attr.c_ospeed = 9600;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == ERROR)
		report_error_fatal(errno);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	rl_catch_signals = FALSE;
	rl_event_hook = signal_event_hook;
}
