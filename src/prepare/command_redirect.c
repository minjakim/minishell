/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 13:01:50 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	command_redirect(t_shell *mini)
{
	const t_redirect	*ptr = mini->command->redirects;
	t_io				*io;

	io = &mini->command->io;
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
	if (!command_io_set(*io))
		return (FAILURE);
	return (SUCCESS);
}
