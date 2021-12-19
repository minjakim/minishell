/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:07:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

T_PTR
	xmalloc(size_t bytes)
{
	T_PTR	temp;

	temp = malloc(bytes);
	if (!temp)
		report_error_fatal(errno);
	return (temp);
}

T_PTR
	xcalloc(size_t bytes)
{
	T_PTR	temp;

	temp = xmalloc(bytes);
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

void
	xfree(void *obj0, void *obj1, void *obj2, void *obj3)
{
	if (obj0)
		free(obj0);
	if (obj1)
		free(obj1);
	if (obj2)
		free(obj2);
	if (obj3)
		free(obj3);
}

pid_t
	xfork(void)
{
	g_status.haschild = fork();
	if (g_status.haschild == ERROR)
		report_error_fatal(errno);
	if (g_status.haschild == 0)
		g_status.interactive = FALSE;
	return (g_status.haschild);
}
