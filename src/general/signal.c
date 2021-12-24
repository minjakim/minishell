/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:30:46 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/22 21:21:53 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	signal_handler(int signum)
{
	(void)signum;
}

int
	signal_event_hook(void)
{
	return (OK);
}

void
	sigint_handler(int signum)
{
	if (signum != SIGINT || !g_status.state.readline)
		return ;
	g_status.exit = GENERAL_ERROR;
	if (g_status.heredoc.value)
	{
		g_status.state.interrupted = TRUE;
		rl_replace_line("", 1);
		rl_done = TRUE;
	}
	else if (g_status.interactive && !g_status.state.haschild)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void
	signal_report(int signum)
{
	char	itoa[2];

	if (g_status.state.haschild)
	{
		g_status.exit += 128;
		if (signum != SIGINT)
		{
			write(STDERR_FILENO, sys_siglist[signum], \
									ft_strlen(sys_siglist[signum]));
			write(STDERR_FILENO, ": ", 2);
			itoa[1] = '0' + (signum % 10);
			if (signum / 10)
				itoa[0] = '0' + ((signum / 10) % 10);
			else
				itoa[0] = '\0';
			write(STDERR_FILENO, itoa, 2);
		}
		write(STDERR_FILENO, "\n", 1);
	}
}

void
	xwait(const pid_t pid, const t_io *const io)
{
	int	stat_loc;

	if (waitpid(pid, &stat_loc, 0) == ERROR)
		report_error(NULL, NULL, errno);
	g_status.exit = stat_loc;
	reset_io(io);
	while (wait(NULL) != ERROR)
		;
	if (g_status.exit && g_status.exit <= SIGUSR2)
		signal_report(g_status.exit);
	else if (g_status.exit > 255)
		g_status.exit >>= 8;
}
