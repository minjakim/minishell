/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:59:03 by snpark            #+#    #+#             */
/*   Updated: 2021/12/06 10:37:17 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>

int
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

	io = &mini->cmd->value.simple.io;
	handle = mini->cmd->value.simple.redirects;
	while (handle)
	{
		if (io->fd[handle->redirector] != handle->redirector)
			close(io->fd[handle->redirector]);
		if (handle->here_doc_eof == NULL)
			io->fd[handle->redirector] = open(handle->redirectee.filename->word, handle->flags);
		else
			io->fd[handle->redirector] = heredoc(handle->here_doc_eof);
		if (io->fd[handle->redirector] == -1)
			return (1);
		handle = handle->next;
	}
	return (0);
}
