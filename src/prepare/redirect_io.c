/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 12:12:11 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	set_io(t_io *io)
{
	if (dup2(io->in, STDIN_FILENO) == ERROR)
		report_error_fatal(errno);
	if (dup2(io->out, STDOUT_FILENO) == ERROR)
		report_error_fatal(errno);
}

void
	reset_io(t_io *io)
{
	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
	set_io(&g_status.backup.stdio);
}

//int
//	redirect_io(t_command *command)
//{
//	const t_redirect	*target = command->redirects;

//	while (target)
//	{
//		if (command->io.fd[target->redirector] != target->redirector)
//			close(command->io.fd[target->redirector]);
//		if (target->here_doc_eof)
//			command->io.fd[target->redirector] = target->redirectee.dest;
//		else
//			command->io.fd[target->redirector] = \
//			open(target->redirectee.filename.word, target->flags, 0644);
//		if (command->io.fd[target->redirector] == ERROR)
//			return (FAILURE);
//		target = target->next;
//	}
//	set_io(&command->io);
//	return (SUCCESS);
//}
int
	redirect_io(t_command *command)
{
	const t_redirect	*ptr = command->redirects;
	t_io				*io;

	io = &command->io;
	while (ptr)
	{
		if (io->fd[ptr->redirector] != ptr->redirector)
			close(io->fd[ptr->redirector]);
		if (ptr->here_doc_eof)
			io->fd[ptr->redirector] = ptr->redirectee.dest;
		else
			io->fd[ptr->redirector] = open(ptr->redirectee.filename.word, \
					ptr->flags, 0644);
		if (io->fd[ptr->redirector] == ERROR)
			return (FAILURE);
		ptr = ptr->next;
	}
	set_io(io);
	return (SUCCESS);
}
