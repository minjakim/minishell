/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:07:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 11:59:32 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

T_PTR
	xcalloc(size_t bytes)
{
	T_PTR	temp;

	temp = malloc(bytes);
	if (!temp)
		report_error_fatal(errno);
	ft_memset(temp, 0, bytes);
	return (temp);
}

T_PTR
	xcalloc_t_command(void)
{
	t_command	*cmd;

	cmd = xcalloc(sizeof(t_command));
	cmd->io.in = STDIN_FILENO;
	cmd->io.out = STDOUT_FILENO;
	return (cmd);
}


pid_t
	xfork(void)
{
	g_status.state.haschild = fork();
	if (g_status.state.haschild == ERROR)
		report_error_fatal(errno);
	if (g_status.state.haschild == 0)
		g_status.interactive = FALSE;
	return (g_status.state.haschild);
}

int
	xpipe(int fd[2], const char *const str)
{
	if (pipe(fd) == ERROR)
	{
		g_status.state.error = report_error("pipe", str, errno);
		return (ERROR);
	}
	return (OK);
}
