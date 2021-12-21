/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/21 08:50:43 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	set_io(const t_io *const io)
{
	if (io->in != STDIN_FILENO)
		if (dup2(io->in, STDIN_FILENO) == ERROR)
			report_error_fatal(errno);
	if (io->out != STDOUT_FILENO)
		if (dup2(io->out, STDOUT_FILENO) == ERROR)
			report_error_fatal(errno);
}

void
	close_io(const t_io *const io)
{
	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
}

void
	reset_io(const t_io *const io)
{
	close_io(io);
	if (io->in != STDIN_FILENO)
		if (dup2(g_status.backup.stdio.in, STDIN_FILENO) == ERROR)
			report_error_fatal(errno);
	if (io->out != STDOUT_FILENO)
		if (dup2(g_status.backup.stdio.out, STDOUT_FILENO) == ERROR)
			report_error_fatal(errno);
}

int
	redirect_io(t_command *cmd)
{
	const t_redirect	*redirects = cmd->redirects;

	while (redirects)
	{
		if (cmd->io.fd[redirects->redirector] != redirects->redirector)
			close(cmd->io.fd[redirects->redirector]);
		if (redirects->redirectee.filename.flags & W_HEREDOC)
			cmd->io.fd[redirects->redirector] = redirects->redirectee.dest;
		else
			cmd->io.fd[redirects->redirector] = \
			open(redirects->redirectee.filename.word, redirects->flags, 0644);
		if (cmd->io.fd[redirects->redirector] == ERROR)
			report_error("open", redirects->redirectee.filename.word, errno);
		redirects = redirects->next;
	}
	return (SUCCESS);
}
