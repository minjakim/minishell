/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:54:15 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	report_error_fatal(const int error)
{
	const char *const	str_error = strerror(error);

	write(STDERR_FILENO, "mini: ", 6);
	write(STDERR_FILENO, str_error, ft_strlen(str_error));
	write(STDERR_FILENO, "\n", 1);
	return (mini_exit(GENERAL_ERROR));
}

int
	report_error(const char *const cmd, const char *const arg, \
								const int error)
{
	const char *const	str_error = strerror(error);

	write(STDERR_FILENO, "mini: ", 6);
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, str_error, ft_strlen(str_error));
	write(STDERR_FILENO, "\n", 1);
	g_status.exit = GENERAL_ERROR;
	if (error == ENOENT)
		return (ENOENT);
	return (g_status.exit);
}

int
	report_error_syntax(const char *const token)
{
	write(STDERR_FILENO, "mini: ", 6);
	write(STDERR_FILENO, EX_SYNTAX, sizeof(EX_SYNTAX));
	if (token)
	{
		write(STDERR_FILENO, " `", 2);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "\'\n", 2);
	}
	g_status.exit = ES_USAGE;
	return (EXCEPTION);
}

int
	report_exception_fatal(const char *const arg, const char *const report, \
															const int error)
{
	write(STDERR_FILENO, "mini: ", 6);
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (report)
		write(STDERR_FILENO, report, ft_strlen(report));
	write(STDERR_FILENO, "\n", 1);
	return (mini_exit(error));
}

int
	report_exception(const char *const cmd, const char *const arg, \
								const char *const report, const int status)
{
	write(STDERR_FILENO, "mini: ", 6);
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (report)
		write(STDERR_FILENO, report, ft_strlen(report));
	write(STDERR_FILENO, "\n", 1);
	return (g_status.exit = status);
}
