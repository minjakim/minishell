/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:30:46 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/19 11:25:06 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	if (g_status.interactive && !g_status.haschild)
	{
		g_status.exit = GENERAL_ERROR;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void
	signal_report(int signum)
{
	char itoa[2];

	if (g_status.interactive && g_status.haschild)
	{
		g_status.exit += 128;
		if (signum != SIGINT)
		{
			write(STDERR_FILENO, sys_siglist[signum], \
									ft_strlen(sys_siglist[signum]));
			write(STDERR_FILENO, ": ", 2);
			itoa[1] = '0' + (signum % 10);
			if (signum /= 10)
				itoa[0] = '0' + (signum % 10);
			else
				itoa[0] = '\0';
			write(STDERR_FILENO, itoa, 2);
		}
		write(STDERR_FILENO, "\n", 1);
	}
}

void
	signal_handler(int signum)
{
	(void)signum;
}
