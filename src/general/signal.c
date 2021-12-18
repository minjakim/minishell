/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:30:46 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/18 15:08:19 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	//if (g_status.heredoc.value)
	//{
	//	close(g_status.heredoc.in);
	//	close(g_status.heredoc.out);
	//	rl_replace_line("", 1);
	//	g_status.setjmp();
	//}
	//else
	//{
	//	write(STDOUT_FILENO, "\n", 1);
	//	rl_on_new_line();
	//	rl_replace_line("", 1);
	//	rl_redisplay();
	//}
	if (g_status.interactive)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}

void
	signal_handler(int signum)
{
	(void)signum;
}
