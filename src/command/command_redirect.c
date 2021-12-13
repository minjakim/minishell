/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 17:04:56 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	heredoc(const char *const eof)
{
	char	*line;

	pipe(g_status.heredoc.fd);
	while (LOOP)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof))
			break ;
		write(g_status.heredoc.out, line, ft_strlen(line));
		write(g_status.heredoc.out, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(g_status.heredoc.out);
	return (g_status.heredoc.in);
}

int
	command_redirect(t_shell *mini)
{
	const t_redirect	*ptr = mini->command->redirects;
	t_io				*io;

	while (ptr)
	{
		if (io->fd[ptr->redirector] != ptr->redirector)
			close(io->fd[ptr->redirector]);
		if (ptr->flags != 0 && ptr->redirectee.filename.word)
			io->fd[ptr->redirector] = open(ptr->redirectee.filename.word, ptr->flags, 0644);
		else if (ptr->flags == 0)
			io->fd[ptr->redirector] = heredoc(ptr->here_doc_eof);
		else
			return (FAILURE);
		if (io->fd[ptr->redirector] == ERROR)
			return (FAILURE);
		ptr = ptr->next;
	}
	if (!command_io_set(io))
		return (FAILURE);
	return (SUCCESS);
}
