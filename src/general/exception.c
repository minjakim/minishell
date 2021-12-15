/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:54:15 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/15 16:08:22 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	exception_error_fatal(const int err_no)
{
	const char *const str_error = strerror(err_no);

	write(STDERR_FILENO, "mnsh: ", 6);
	write(STDERR_FILENO, str_error, strlen(str_error));
	write(STDERR_FILENO, "\n", 1);
	exit(ERR_NO_GENERAL);
}

int
	exception_error(const char *const cmd, const char *const arg, \
								const int err_no)
{
	const char *const str_error = strerror(err_no);

	write(STDERR_FILENO, "mnsh: ", 6);
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
	write(STDERR_FILENO, str_error, strlen(str_error));
	write(STDERR_FILENO, "\n", 1);
	return (ERR_NO_GENERAL);
}

int
	exception_report(const char *const cmd, const char *const arg, \
								const char *const msg, const int err_no)
{
	write(STDERR_FILENO, "mnsh: ", 6);
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
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (err_no);
}
