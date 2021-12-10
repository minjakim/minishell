/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/10 13:13:10 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>

static int
	is_eof(char **line, const char *const eof)
{
	*line = readline("heredoc> ");
	if (*line && strcmp(*line, eof))
		return (1);
	return (0);
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
		write(io.fd[1], line, strlen(line));
		write(io.fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(io.fd[1]);
	return (io.fd[0]);
}

int
	redirect(t_shell *mini)
{
	t_redirect *handle;
	t_io		*io;

	while (handle)
	{
		if (io->fd[handle->redirector] != handle->redirector)
			close(io->fd[handle->redirector]);
		if (handle->flags != 0 && handle->redirectee.filename.word)
			io->fd[handle->redirector] = open(handle->redirectee.filename.word, handle->flags, 0644);
		else if (handle->flags == 0)
			io->fd[handle->redirector] = heredoc(handle->here_doc_eof);
		else
			return (1);
		if (io->fd[handle->redirector] == -1)
			return (1);
		handle = handle->next;
	}
	if (redirect_stdio(*io) != 0)
		return (1);
	return (0);
}
