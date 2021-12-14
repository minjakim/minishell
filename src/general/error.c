/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:23:36 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/14 19:28:50 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	error_fatal(const char *const str, const size_t nbyte)
{
	write(STDERR_FILENO, str, nbyte);
}

int
	error_report(const char *cmd, const char *const arg, const char *const msg, const int error_no)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (arg)
		printf("bash: %s: %s: %s\n", cmd, arg, msg);
	else
		printf("bash: %s: %s\n", cmd, msg);
	dup2(g_status.backup.stdio.out, STDOUT_FILENO);
	return (error_no);
}
