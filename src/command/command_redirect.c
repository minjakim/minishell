/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/12 15:27:03 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	is_eof(char **line, const char *const eof)
{
	*line = readline("heredoc> ");
	if (*line && ft_strcmp(*line, eof))
		return (TRUE);
	return (FALSE);
}

static int
	heredoc(const char *const eof)
{
	char	*line;
	t_io	io;

	line = NULL;
	pipe(io.fd);
	while (is_eof(&line, eof))
	{
		write(io.fd[1], line, ft_strlen(line));
		write(io.fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(io.fd[1]);
	return (io.fd[0]);
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
			return (FAIL);
		if (io->fd[ptr->redirector] == ERROR)
			return (FAIL);
		ptr = ptr->next;
	}
	if (!command_io_set(io))
		return (FAIL);
	return (SUCCESS);
}
