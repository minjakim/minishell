/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 13:08:49 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	redirect(t_command *cmd)
{
	const t_redirect	*ptr = cmd->redirects;
	t_io				*io;

	io = &cmd->io;
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
	if (!cmd_io_set(*io))
		return (FAILURE);
	return (SUCCESS);
}
